[CmdletBinding()]
param(
    [string]$ProductVersion = '3.8.8'
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$RepositoryRoot = [IO.Path]::GetFullPath((Split-Path -Parent $PSScriptRoot))
$DistRoot = Join-Path $RepositoryRoot 'dist'
$ArtifactRoot = Join-Path $RepositoryRoot 'artifacts'
$PayloadRoot = Join-Path $ArtifactRoot 'payload'
$LogRoot = Join-Path $ArtifactRoot 'test-logs'
$InstallRoot = Join-Path $env:ProgramFiles 'AstroFocus Studio'
$BundlePath = Join-Path $DistRoot "AstroFocusStudio-$ProductVersion-Setup.exe"
$MsiPath = Join-Path $DistRoot "AstroFocusStudio-$ProductVersion-x64.msi"
$ManifestPath = Join-Path $PayloadRoot 'release-manifest.json'

New-Item -ItemType Directory -Force -Path $LogRoot | Out-Null

function Quote-NativeArgument([string]$Value) {
    return '"' + $Value.Replace('"', '\"') + '"'
}

function Invoke-InstallerProcess {
    param(
        [Parameter(Mandatory = $true)][string]$FilePath,
        [Parameter(Mandatory = $true)][string[]]$Arguments,
        [Parameter(Mandatory = $true)][string]$Description,
        [int[]]$SuccessExitCodes = @(0, 1641, 3010)
    )

    Write-Host "==> $Description"
    $argumentLine = ($Arguments | ForEach-Object { Quote-NativeArgument $_ }) -join ' '
    $process = Start-Process -FilePath $FilePath -ArgumentList $argumentLine -Wait -PassThru
    if ($SuccessExitCodes -notcontains $process.ExitCode) {
        throw "$Description ist fehlgeschlagen (Exitcode $($process.ExitCode))."
    }
}

function Assert-InstalledPayload {
    if (-not (Test-Path -LiteralPath $InstallRoot -PathType Container)) {
        throw "Installationsverzeichnis fehlt: $InstallRoot"
    }
    if (-not (Test-Path -LiteralPath $ManifestPath -PathType Leaf)) {
        throw "Buildmanifest fehlt: $ManifestPath"
    }

    $manifest = Get-Content -LiteralPath $ManifestPath -Raw | ConvertFrom-Json
    foreach ($file in $manifest.files) {
        $installed = Join-Path $InstallRoot ([string]$file.path).Replace('/', '\')
        if (-not (Test-Path -LiteralPath $installed -PathType Leaf)) {
            throw "Installierte Datei fehlt: $installed"
        }
        $actualHash = (Get-FileHash -Algorithm SHA256 -LiteralPath $installed).Hash.ToLowerInvariant()
        if ($actualHash -ne [string]$file.sha256) {
            throw "Prüfsumme der installierten Datei stimmt nicht: $installed"
        }
    }
}

function Assert-Uninstalled {
    if (Test-Path -LiteralPath $InstallRoot) {
        $remaining = @(Get-ChildItem -LiteralPath $InstallRoot -Force -ErrorAction SilentlyContinue)
        if ($remaining.Count -gt 0) {
            throw "Nach der Deinstallation sind Dateien übrig: $InstallRoot"
        }
        Remove-Item -LiteralPath $InstallRoot -Force -ErrorAction SilentlyContinue
    }
}

function Invoke-HealthCheck {
    $engine = Join-Path $InstallRoot 'AstroFocusEngine.exe'
    $cameraHost = Join-Path $InstallRoot 'AstroFocusCameraHost.exe'
    $focuserHost = Join-Path $InstallRoot 'AstroFocusFocuserHost.exe'
    foreach ($program in @($engine, $cameraHost, $focuserHost)) {
        Invoke-InstallerProcess -FilePath $program -Arguments @('--health-check') -Description "Health-Check $([IO.Path]::GetFileName($program))" -SuccessExitCodes @(0)
    }
}

foreach ($required in @($BundlePath, $MsiPath, $ManifestPath)) {
    if (-not (Test-Path -LiteralPath $required -PathType Leaf)) {
        throw "Erforderliches Buildartefakt fehlt: $required"
    }
}

$bundleInstallLog = Join-Path $LogRoot 'bundle-install.log'
$bundleRepairLog = Join-Path $LogRoot 'bundle-repair.log'
$bundleUninstallLog = Join-Path $LogRoot 'bundle-uninstall.log'
$msiInstallLog = Join-Path $LogRoot 'msi-install.log'
$msiUninstallLog = Join-Path $LogRoot 'msi-uninstall.log'

try {
    # Burn bundle: install, verify every payload hash, exercise repair, then uninstall.
    Invoke-InstallerProcess -FilePath $BundlePath -Arguments @('/install', '/quiet', '/norestart', '/log', $bundleInstallLog) -Description 'Bundle-Installation'
    Assert-InstalledPayload
    Invoke-HealthCheck

    $repairProbe = Join-Path $InstallRoot 'AstroFocusFocuserHost.exe'
    Remove-Item -LiteralPath $repairProbe -Force
    if (Test-Path -LiteralPath $repairProbe) {
        throw 'Die Reparatur-Testdatei konnte nicht entfernt werden.'
    }
    Invoke-InstallerProcess -FilePath $BundlePath -Arguments @('/repair', '/quiet', '/norestart', '/log', $bundleRepairLog) -Description 'Bundle-Reparatur'
    Assert-InstalledPayload

    Invoke-InstallerProcess -FilePath $BundlePath -Arguments @('/uninstall', '/quiet', '/norestart', '/log', $bundleUninstallLog) -Description 'Bundle-Deinstallation'
    Assert-Uninstalled

    # Raw MSI: prove that the MSI is independently installable and removable.
    Invoke-InstallerProcess -FilePath 'msiexec.exe' -Arguments @('/i', $MsiPath, '/qn', '/norestart', '/l*v', $msiInstallLog) -Description 'MSI-Installation'
    Assert-InstalledPayload
    Invoke-HealthCheck
    Invoke-InstallerProcess -FilePath 'msiexec.exe' -Arguments @('/x', $MsiPath, '/qn', '/norestart', '/l*v', $msiUninstallLog) -Description 'MSI-Deinstallation'
    Assert-Uninstalled
} finally {
    if (Test-Path -LiteralPath $InstallRoot) {
        try {
            Invoke-InstallerProcess -FilePath 'msiexec.exe' -Arguments @('/x', $MsiPath, '/qn', '/norestart', '/l*v', (Join-Path $LogRoot 'cleanup-uninstall.log')) -Description 'Bereinigungs-Deinstallation' -SuccessExitCodes @(0, 1605, 1614, 1641, 3010)
        } catch {
            Write-Warning $_
        }
    }
}

Write-Host 'Bundle- und MSI-Installation, Reparatur, Health-Checks und Deinstallation wurden bestanden.'
