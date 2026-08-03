[CmdletBinding()]
param(
    [string]$ProductVersion = '',
    [string]$BundleVersion = '',
    [string]$WixVersion = '5.0.2',
    [switch]$SkipPythonTests
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$RepositoryRoot = [IO.Path]::GetFullPath((Split-Path -Parent $PSScriptRoot))
$RepositoryVersion = & (Join-Path $PSScriptRoot 'Get-RepositoryVersion.ps1') -RepositoryRoot $RepositoryRoot
if ([string]::IsNullOrWhiteSpace($ProductVersion)) { $ProductVersion = $RepositoryVersion.Product }
if ([string]::IsNullOrWhiteSpace($BundleVersion)) { $BundleVersion = $RepositoryVersion.Bundle }
$ArtifactsRoot = Join-Path $RepositoryRoot 'artifacts'
$DistRoot = Join-Path $RepositoryRoot 'dist'
$PayloadRoot = Join-Path $ArtifactsRoot 'payload'
$InstallerOutput = Join-Path $ArtifactsRoot 'installer'
$ToolRoot = Join-Path $ArtifactsRoot 'tools'
$LogRoot = Join-Path $ArtifactsRoot 'test-logs'


$payloadFiles = [ordered]@{
    'AstroFocusUpdater.ps1'          = 'updater\AstroFocusUpdater.ps1'
    'AstroFocusSetup.ps1'            = 'installer\AstroFocusSetup.ps1'
    'update-public-key.cer'           = 'updater\update-public-key.cer'
    'README_DE.md'                    = 'README_DE.md'
    'KNOWN_LIMITATIONS.txt'           = 'KNOWN_LIMITATIONS.txt'
    'UNSIGNED_DEVELOPMENT_BUILD.txt'  = 'UNSIGNED_DEVELOPMENT_BUILD.txt'
}

$packagingInputs = @(
    'release\New-ReleaseManifest.ps1',
    'installer\build-wix.ps1',
    'installer\wix\Package.wxs',
    'installer\wix\Bundle.wxs'
) + @($payloadFiles.Values)

function Assert-PackagingInputs {
    $missing = @()
    foreach ($relativePath in $packagingInputs) {
        $source = Join-Path $RepositoryRoot $relativePath
        if (-not (Test-Path -LiteralPath $source -PathType Leaf)) {
            $missing += $relativePath
        }
    }
    if ($missing.Count -gt 0) {
        throw "Erforderliche Paketquelldateien fehlen: $($missing -join ', ')"
    }
}

function Add-PathEntry([string]$Path) {
    if (-not [string]::IsNullOrWhiteSpace($Path) -and
        (Test-Path -LiteralPath $Path -PathType Container) -and
        -not (($env:Path -split ';') -contains $Path)) {
        $env:Path = "$Path;$env:Path"
    }
}

function Initialize-LlvmPath {
    $candidates = @(
        (Join-Path $env:ProgramFiles 'LLVM\bin'),
        (Join-Path $env:ProgramFiles 'Microsoft Visual Studio\2022\Enterprise\VC\Tools\Llvm\x64\bin'),
        (Join-Path $env:ProgramFiles 'Microsoft Visual Studio\2022\Professional\VC\Tools\Llvm\x64\bin'),
        (Join-Path $env:ProgramFiles 'Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\x64\bin')
    )
    foreach ($candidate in $candidates) {
        Add-PathEntry $candidate
    }

    foreach ($tool in @('clang.exe', 'clang-cl.exe', 'lld-link.exe')) {
        if ($null -eq (Get-Command $tool -ErrorAction SilentlyContinue)) {
            throw "Erforderliches LLVM-Werkzeug fehlt: $tool"
        }
    }
}

function Remove-GeneratedNativeFiles {
    $componentDirectories = @('frontend', 'backend', 'focuser_setup', 'device_host', 'tools')
    foreach ($directory in $componentDirectories) {
        $path = Join-Path $RepositoryRoot $directory
        Get-ChildItem -LiteralPath $path -File -ErrorAction Stop |
            Where-Object { $_.Extension -in @('.obj', '.exe', '.pdb', '.ilk', '.exp', '.map') -or $_.Name -like '*_stub.dll' } |
            Remove-Item -Force
    }
}

function Assert-Pe64([string]$Path) {
    $bytes = [IO.File]::ReadAllBytes($Path)
    if ($bytes.Length -lt 256 -or $bytes[0] -ne 0x4d -or $bytes[1] -ne 0x5a) {
        throw "Keine gültige PE-Datei: $Path"
    }
    $peOffset = [BitConverter]::ToInt32($bytes, 0x3c)
    if ($peOffset -lt 0 -or $peOffset + 26 -gt $bytes.Length) {
        throw "Ungültiger PE-Header: $Path"
    }
    if ($bytes[$peOffset] -ne 0x50 -or $bytes[$peOffset + 1] -ne 0x45 -or
        $bytes[$peOffset + 2] -ne 0 -or $bytes[$peOffset + 3] -ne 0) {
        throw "PE-Signatur fehlt: $Path"
    }
    $machine = [BitConverter]::ToUInt16($bytes, $peOffset + 4)
    $optionalMagic = [BitConverter]::ToUInt16($bytes, $peOffset + 24)
    if ($machine -ne 0x8664 -or $optionalMagic -ne 0x20b) {
        throw "Binärdatei ist nicht Windows x64/PE32+: $Path"
    }
}

function Invoke-Checked([scriptblock]$Command, [string]$FailureMessage) {
    & $Command
    if ($LASTEXITCODE -ne 0) {
        throw "$FailureMessage (Exitcode $LASTEXITCODE)"
    }
}

Assert-PackagingInputs
Initialize-LlvmPath
Remove-GeneratedNativeFiles
# Keep test-logs across build cleanup so a failing CI step still uploads diagnostics.
Remove-Item -LiteralPath $PayloadRoot -Recurse -Force -ErrorAction SilentlyContinue
Remove-Item -LiteralPath $InstallerOutput -Recurse -Force -ErrorAction SilentlyContinue
Remove-Item -LiteralPath $ToolRoot -Recurse -Force -ErrorAction SilentlyContinue
Remove-Item -LiteralPath $DistRoot -Recurse -Force -ErrorAction SilentlyContinue
New-Item -ItemType Directory -Force -Path $ArtifactsRoot, $DistRoot, $PayloadRoot, $InstallerOutput, $ToolRoot, $LogRoot | Out-Null

Write-Host 'LLVM-Versionen:'
& clang.exe --version
& clang-cl.exe --version
& lld-link.exe --version

Push-Location $RepositoryRoot
try {
    & cmd.exe /d /s /c 'call build-all-windows-x64.bat'
    if ($LASTEXITCODE -ne 0) {
        throw "Der Windows-x64-Gesamtbuild ist fehlgeschlagen (Exitcode $LASTEXITCODE)."
    }
} finally {
    Pop-Location
}

$binaryMap = [ordered]@{
    'AstroFocusStudio.exe'       = 'out\windows-x64\bin\AstroFocusStudio.exe'
    'AstroFocusEngine.exe'       = 'out\windows-x64\bin\AstroFocusEngine.exe'
    'AstroFocusCameraHost.exe'   = 'out\windows-x64\bin\AstroFocusCameraHost.exe'
    'AstroFocusFocuserHost.exe'  = 'out\windows-x64\bin\AstroFocusFocuserHost.exe'
    'AstroFocusFocuserSetup.exe' = 'out\windows-x64\bin\AstroFocusFocuserSetup.exe'
    'AstroFocusUpdater.exe'      = 'out\windows-x64\bin\AstroFocusUpdater.exe'
    'AstroFocusSetup.exe'        = 'out\windows-x64\bin\AstroFocusSetup.exe'
}

foreach ($entry in $binaryMap.GetEnumerator()) {
    $source = Join-Path $RepositoryRoot $entry.Value
    if (-not (Test-Path -LiteralPath $source -PathType Leaf)) {
        throw "Buildausgabe fehlt: $($entry.Key)"
    }
    Assert-Pe64 $source
    Copy-Item -LiteralPath $source -Destination (Join-Path $PayloadRoot $entry.Key) -Force
}

if (-not $SkipPythonTests) {
    $pythonLog = Join-Path $LogRoot 'python-tests.log'
    & (Join-Path $PSScriptRoot 'Run-PythonTests.ps1') `
        -RepositoryRoot $RepositoryRoot `
        -LogPath $pythonLog
}

foreach ($entry in $payloadFiles.GetEnumerator()) {
    $source = Join-Path $RepositoryRoot $entry.Value
    if (-not (Test-Path -LiteralPath $source -PathType Leaf)) {
        throw "Payload-Quelldatei fehlt: $($entry.Value)"
    }
    Copy-Item -LiteralPath $source -Destination (Join-Path $PayloadRoot $entry.Key) -Force
}

& (Join-Path $RepositoryRoot 'release\New-ReleaseManifest.ps1') -Payload $PayloadRoot -Version $ProductVersion
if (-not (Test-Path -LiteralPath (Join-Path $PayloadRoot 'release-manifest.json'))) {
    throw 'Das Release-Manifest konnte nicht erzeugt werden.'
}

$dotnet = Get-Command dotnet.exe -ErrorAction SilentlyContinue
if ($null -eq $dotnet) {
    $dotnet = Get-Command dotnet -ErrorAction SilentlyContinue
}
if ($null -eq $dotnet) {
    throw '.NET SDK wurde nicht gefunden; WiX kann nicht installiert werden.'
}

$wixExe = Join-Path $ToolRoot 'wix.exe'
if (-not (Test-Path -LiteralPath $wixExe -PathType Leaf)) {
    & $dotnet.Source tool install --tool-path $ToolRoot wix --version $WixVersion
    if ($LASTEXITCODE -ne 0) {
        throw "WiX $WixVersion konnte nicht als lokales .NET-Tool installiert werden."
    }
}

& (Join-Path $RepositoryRoot 'installer\build-wix.ps1') `
    -Payload $PayloadRoot `
    -Output $InstallerOutput `
    -ProductVersion $ProductVersion `
    -BundleVersion $BundleVersion `
    -WixVersion $WixVersion `
    -WixExe $wixExe `
    -DevelopmentBuild

$msiSource = Join-Path $InstallerOutput "AstroFocusStudio-$ProductVersion-x64.msi"
$setupSource = Join-Path $InstallerOutput "AstroFocusStudio-$ProductVersion-Setup.exe"
$msiTarget = Join-Path $DistRoot "AstroFocusStudio-$ProductVersion-x64.msi"
$setupTarget = Join-Path $DistRoot "AstroFocusStudio-$ProductVersion-Setup.exe"
Copy-Item -LiteralPath $msiSource -Destination $msiTarget -Force
Copy-Item -LiteralPath $setupSource -Destination $setupTarget -Force

$portableZip = Join-Path $DistRoot "AstroFocusStudio-$ProductVersion-Portable-Windows-x64.zip"
Compress-Archive -Path (Join-Path $PayloadRoot '*') -DestinationPath $portableZip -CompressionLevel Optimal -Force

$sourceZip = Join-Path $DistRoot "AstroFocusStudio-$ProductVersion-Source.zip"
$git = Get-Command git.exe -ErrorAction SilentlyContinue
if ($null -eq $git) {
    $git = Get-Command git -ErrorAction SilentlyContinue
}
if ($null -ne $git -and (Test-Path -LiteralPath (Join-Path $RepositoryRoot '.git') -PathType Container)) {
    & $git.Source -C $RepositoryRoot archive --format=zip --output=$sourceZip HEAD
    if ($LASTEXITCODE -ne 0) {
        throw 'Das Quellarchiv konnte mit git archive nicht erzeugt werden.'
    }
}

$commit = 'unbekannt'
if ($null -ne $git -and (Test-Path -LiteralPath (Join-Path $RepositoryRoot '.git') -PathType Container)) {
    $commit = (& $git.Source -C $RepositoryRoot rev-parse HEAD).Trim()
}
$buildInfo = @(
    'AstroFocus Studio GitHub Actions Build',
    "Version: $ProductVersion",
    "Commit: $commit",
    "UTC: $([DateTime]::UtcNow.ToString('o'))",
    "WiX: $WixVersion",
    "Runner OS: $([Environment]::OSVersion.VersionString)",
    '',
    'Dieser Build ist nicht Authenticode-signiert.'
)
$buildInfo | Set-Content -LiteralPath (Join-Path $DistRoot 'BUILD_INFO.txt') -Encoding utf8

$checksumLines = Get-ChildItem -LiteralPath $DistRoot -File |
    Where-Object { $_.Name -ne 'SHA256SUMS.txt' } |
    Sort-Object Name |
    ForEach-Object {
        $hash = (Get-FileHash -Algorithm SHA256 -LiteralPath $_.FullName).Hash.ToLowerInvariant()
        "$hash  $($_.Name)"
    }
$checksumLines | Set-Content -LiteralPath (Join-Path $DistRoot 'SHA256SUMS.txt') -Encoding ascii

Write-Host 'Erzeugte GitHub-Artefakte:'
Get-ChildItem -LiteralPath $DistRoot -File | Sort-Object Name | Format-Table Name, Length -AutoSize
