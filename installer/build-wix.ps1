[CmdletBinding()]
param(
    [string]$Payload='',

    [string]$Output='',

    [string]$ProductVersion = '3.8.8',
    [string]$BundleVersion = '3.8.8.0',
    [string]$WixVersion = '5.0.2',
    [string]$WixExe = 'wix.exe',
    [switch]$DevelopmentBuild
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$ScriptDirectory = $PSScriptRoot
if ([string]::IsNullOrWhiteSpace($ScriptDirectory) -and
    -not [string]::IsNullOrWhiteSpace([string]$MyInvocation.MyCommand.Path)) {
    $ScriptDirectory = Split-Path -Parent $MyInvocation.MyCommand.Path
}
if ([string]::IsNullOrWhiteSpace($ScriptDirectory)) {
    throw 'Der Verzeichnisort des WiX-Buildskripts konnte nicht bestimmt werden.'
}
if ([string]::IsNullOrWhiteSpace($Payload)) {
    $Payload = Join-Path -Path $ScriptDirectory -ChildPath 'payload'
}
if ([string]::IsNullOrWhiteSpace($Output)) {
    $Output = Join-Path -Path $ScriptDirectory -ChildPath 'out'
}

$payloadFull = [IO.Path]::GetFullPath($Payload)
$outputFull = [IO.Path]::GetFullPath($Output)
if (-not (Test-Path -LiteralPath $payloadFull -PathType Container)) {
    throw "Der Installer-Payload fehlt: $payloadFull"
}
New-Item -ItemType Directory -Force -Path $outputFull | Out-Null

$wixCommand = Get-Command $WixExe -ErrorAction SilentlyContinue
if ($null -eq $wixCommand) {
    if (Test-Path -LiteralPath $WixExe -PathType Leaf) {
        $wixPath = [IO.Path]::GetFullPath($WixExe)
    } else {
        throw "WiX Toolset wurde nicht gefunden: $WixExe"
    }
} else {
    $wixPath = $wixCommand.Source
}

$packageSource = Join-Path $ScriptDirectory 'wix\Package.wxs'
$bundleSource = Join-Path $ScriptDirectory 'wix\Bundle.wxs'
$msiPath = Join-Path $outputFull "AstroFocusStudio-$ProductVersion-x64.msi"
$bundlePath = Join-Path $outputFull "AstroFocusStudio-$ProductVersion-Setup.exe"
$intermediate = Join-Path $outputFull 'intermediate'
$extensionRef = "WixToolset.BootstrapperApplications.wixext/$WixVersion"
$iconPath = [IO.Path]::GetFullPath((Join-Path $ScriptDirectory '..\frontend\AstroFocusStudio.ico'))

foreach ($required in @($packageSource, $bundleSource, $iconPath)) {
    if (-not (Test-Path -LiteralPath $required -PathType Leaf)) {
        throw "WiX-Quelldatei fehlt: $required"
    }
}

Push-Location $outputFull
try {
    & $wixPath --version
    if ($LASTEXITCODE -ne 0) {
        throw 'WiX konnte nicht gestartet werden.'
    }

    # Use a repository-local extension cache. This avoids depending on whatever
    # WiX version happens to be preinstalled on a hosted runner.
    & $wixPath extension add $extensionRef
    if ($LASTEXITCODE -ne 0) {
        throw "Die WiX-Bootstrapper-Erweiterung konnte nicht geladen werden: $extensionRef"
    }

    $packageArguments = @(
        'build', $packageSource,
        '-arch', 'x64',
        '-d', "Payload=$payloadFull",
        '-d', "ProductVersion=$ProductVersion",
        '-d', "IconPath=$iconPath",
        '-intermediateFolder', (Join-Path $intermediate 'msi'),
        '-pdbtype', 'none',
        '-o', $msiPath
    )
    if ($DevelopmentBuild) {
        $packageArguments += @('-d', 'DevelopmentBuild=1')
    }

    & $wixPath @packageArguments
    if ($LASTEXITCODE -ne 0) {
        throw 'MSI-Build fehlgeschlagen.'
    }

    & $wixPath build $bundleSource `
        -ext $extensionRef `
        -d "MsiPath=$msiPath" `
        -d "BundleVersion=$BundleVersion" `
        -d "IconPath=$iconPath" `
        -intermediateFolder (Join-Path $intermediate 'bundle') `
        -pdbtype none `
        -o $bundlePath
    if ($LASTEXITCODE -ne 0) {
        throw 'Bundle-Build fehlgeschlagen.'
    }
} finally {
    Pop-Location
}

foreach ($result in @($msiPath, $bundlePath)) {
    if (-not (Test-Path -LiteralPath $result -PathType Leaf) -or
        (Get-Item -LiteralPath $result).Length -le 0) {
        throw "Der erwartete Installer wurde nicht erzeugt: $result"
    }
}

Remove-Item -LiteralPath $intermediate -Recurse -Force -ErrorAction SilentlyContinue
Remove-Item -LiteralPath (Join-Path $outputFull '.wix') -Recurse -Force -ErrorAction SilentlyContinue

Write-Host "MSI erstellt: $msiPath"
Write-Host "Setup erstellt: $bundlePath"
