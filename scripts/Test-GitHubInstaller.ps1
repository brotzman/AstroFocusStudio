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
$SmokeLog = Join-Path $LogRoot 'installer-smoke.log'

New-Item -ItemType Directory -Force -Path $LogRoot | Out-Null
Set-Content -LiteralPath $SmokeLog -Value '' -Encoding utf8

function Write-SmokeLog([string]$Message) {
    $line = "[{0}] {1}" -f ([DateTime]::UtcNow.ToString('o')), $Message
    $line | Tee-Object -FilePath $SmokeLog -Append | Write-Host
}

function Quote-NativeArgument([string]$Value) {
    if ($null -eq $Value) { return '""' }
    return '"' + $Value.Replace('"', '\"') + '"'
}

function Stop-ProcessTree([int]$ProcessId) {
    if ($ProcessId -le 0) { return }
    try {
        & taskkill.exe /PID $ProcessId /T /F 2>&1 | ForEach-Object { Write-SmokeLog "taskkill: $_" }
    } catch {
        Write-SmokeLog "WARN: Prozessbaum $ProcessId konnte nicht vollständig beendet werden: $($_.Exception.Message)"
    }
}

function Invoke-InstallerProcess {
    param(
        [Parameter(Mandatory = $true)][string]$FilePath,
        [Parameter(Mandatory = $true)][string[]]$Arguments,
        [Parameter(Mandatory = $true)][string]$Description,
        [int[]]$SuccessExitCodes = @(0, 1641, 3010),
        [ValidateRange(1, 900)][int]$TimeoutSeconds = 180
    )

    $argumentLine = ($Arguments | ForEach-Object { Quote-NativeArgument $_ }) -join ' '
    Write-SmokeLog "START: $Description"
    Write-SmokeLog "COMMAND: $FilePath $argumentLine"
    Write-SmokeLog "TIMEOUT: $TimeoutSeconds seconds"

    $startInfo = New-Object System.Diagnostics.ProcessStartInfo
    $startInfo.FileName = $FilePath
    $startInfo.Arguments = $argumentLine
    $startInfo.WorkingDirectory = $RepositoryRoot
    $startInfo.UseShellExecute = $false
    $startInfo.CreateNoWindow = $true

    $process = New-Object System.Diagnostics.Process
    $process.StartInfo = $startInfo
    try {
        if (-not $process.Start()) {
            throw "$Description konnte nicht gestartet werden."
        }
        Write-SmokeLog "PID: $($process.Id)"

        # Deliberately wait only for the direct process handle. Start-Process -Wait can
        # wait for an entire descendant tree and may never return after Burn/MSI work.
        if (-not $process.WaitForExit($TimeoutSeconds * 1000)) {
            $childProcessId = $process.Id
            Write-SmokeLog "TIMEOUT: $Description exceeded $TimeoutSeconds seconds (PID $childProcessId)."
            Stop-ProcessTree -ProcessId $childProcessId
            throw "$Description hat das Zeitlimit von $TimeoutSeconds Sekunden überschritten. Details: $SmokeLog"
        }

        # Flush asynchronous process state before reading ExitCode.
        $process.WaitForExit()
        $exitCode = $process.ExitCode
        Write-SmokeLog "END: $Description, exit code $exitCode"
        if ($SuccessExitCodes -notcontains $exitCode) {
            throw "$Description ist fehlgeschlagen (Exitcode $exitCode). Details: $SmokeLog"
        }
    } finally {
        $process.Dispose()
    }
}

function Assert-InstalledPayload {
    Write-SmokeLog 'VERIFY: installed payload and SHA-256 manifest'
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
    Write-SmokeLog 'PASS: installed payload and hashes'
}

function Assert-Uninstalled {
    Write-SmokeLog 'VERIFY: installation directory removed'
    if (Test-Path -LiteralPath $InstallRoot) {
        $remaining = @(Get-ChildItem -LiteralPath $InstallRoot -Force -ErrorAction SilentlyContinue)
        if ($remaining.Count -gt 0) {
            throw "Nach der Deinstallation sind Dateien übrig: $InstallRoot"
        }
        Remove-Item -LiteralPath $InstallRoot -Force -ErrorAction SilentlyContinue
    }
    Write-SmokeLog 'PASS: product removed'
}

function Invoke-HealthCheck {
    $engine = Join-Path $InstallRoot 'AstroFocusEngine.exe'
    $cameraHost = Join-Path $InstallRoot 'AstroFocusCameraHost.exe'
    $focuserHost = Join-Path $InstallRoot 'AstroFocusFocuserHost.exe'
    foreach ($program in @($engine, $cameraHost, $focuserHost)) {
        Invoke-InstallerProcess `
            -FilePath $program `
            -Arguments @('--health-check') `
            -Description "Health-Check $([IO.Path]::GetFileName($program))" `
            -SuccessExitCodes @(0) `
            -TimeoutSeconds 30
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

Write-SmokeLog "Installer smoke test started for AstroFocus Studio $ProductVersion"
try {
    # Burn bundle: install, verify every payload hash, exercise repair, then uninstall.
    # Installation is Burn's default action; /install is intentionally omitted because
    # WixStdBA reports it as an unknown argument.
    Invoke-InstallerProcess -FilePath $BundlePath -Arguments @('/quiet', '/norestart', '/log', $bundleInstallLog) -Description 'Bundle-Installation' -TimeoutSeconds 180
    Assert-InstalledPayload
    Invoke-HealthCheck

    $repairProbe = Join-Path $InstallRoot 'AstroFocusFocuserHost.exe'
    Remove-Item -LiteralPath $repairProbe -Force
    if (Test-Path -LiteralPath $repairProbe) {
        throw 'Die Reparatur-Testdatei konnte nicht entfernt werden.'
    }
    Invoke-InstallerProcess -FilePath $BundlePath -Arguments @('/repair', '/quiet', '/norestart', '/log', $bundleRepairLog) -Description 'Bundle-Reparatur' -TimeoutSeconds 180
    Assert-InstalledPayload

    Invoke-InstallerProcess -FilePath $BundlePath -Arguments @('/uninstall', '/quiet', '/norestart', '/log', $bundleUninstallLog) -Description 'Bundle-Deinstallation' -TimeoutSeconds 180
    Assert-Uninstalled

    # Raw MSI: prove that the MSI is independently installable and removable.
    Invoke-InstallerProcess -FilePath 'msiexec.exe' -Arguments @('/i', $MsiPath, '/qn', '/norestart', '/l*v', $msiInstallLog) -Description 'MSI-Installation' -TimeoutSeconds 180
    Assert-InstalledPayload
    Invoke-HealthCheck
    Invoke-InstallerProcess -FilePath 'msiexec.exe' -Arguments @('/x', $MsiPath, '/qn', '/norestart', '/l*v', $msiUninstallLog) -Description 'MSI-Deinstallation' -TimeoutSeconds 180
    Assert-Uninstalled
} finally {
    if (Test-Path -LiteralPath $InstallRoot) {
        try {
            Invoke-InstallerProcess -FilePath 'msiexec.exe' -Arguments @('/x', $MsiPath, '/qn', '/norestart', '/l*v', (Join-Path $LogRoot 'cleanup-uninstall.log')) -Description 'Bereinigungs-Deinstallation' -SuccessExitCodes @(0, 1605, 1614, 1641, 3010) -TimeoutSeconds 120
        } catch {
            Write-Warning $_
            Write-SmokeLog "WARN: cleanup failed: $($_.Exception.Message)"
        }
    }
}

Write-SmokeLog 'PASS: Bundle and MSI install, repair, health checks and uninstall'
Write-Host 'Bundle- und MSI-Installation, Reparatur, Health-Checks und Deinstallation wurden bestanden.'
