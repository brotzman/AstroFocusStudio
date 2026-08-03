[CmdletBinding()]
param(
    [string]$ProductVersion = '3.9.0',
    [ValidateSet('Bundle', 'Msi')][string]$Mode = 'Bundle',
    [string]$RepositoryRoot = ''
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

if ([string]::IsNullOrWhiteSpace($RepositoryRoot)) {
    $RepositoryRoot = Split-Path -Parent $PSScriptRoot
}
$RepositoryRoot = [IO.Path]::GetFullPath($RepositoryRoot)
$DistRoot = Join-Path $RepositoryRoot 'dist'
$ArtifactRoot = Join-Path $RepositoryRoot 'artifacts'
$PayloadRoot = Join-Path $ArtifactRoot 'payload'
$LogRoot = Join-Path $ArtifactRoot 'test-logs'
$InstallRoot = Join-Path $env:ProgramFiles 'AstroFocus Studio'
$CommonDesktopRoot = [Environment]::GetFolderPath([Environment+SpecialFolder]::CommonDesktopDirectory)
if ([string]::IsNullOrWhiteSpace($CommonDesktopRoot)) {
    throw 'Der gemeinsame Windows-Desktoppfad konnte nicht ermittelt werden.'
}
$DesktopShortcutPath = Join-Path $CommonDesktopRoot 'AstroFocus Studio.lnk'
$BundlePath = Join-Path $DistRoot "AstroFocusStudio-$ProductVersion-Setup.exe"
$MsiPath = Join-Path $DistRoot "AstroFocusStudio-$ProductVersion-x64.msi"
$MsiExecPath = Join-Path $env:SystemRoot 'System32\msiexec.exe'
$ManifestPath = Join-Path $PayloadRoot 'release-manifest.json'
$SmokeLog = Join-Path $LogRoot 'installer-smoke.log'

New-Item -ItemType Directory -Force -Path $LogRoot | Out-Null
$Utf8NoBom = New-Object System.Text.UTF8Encoding($false)
[IO.File]::WriteAllText($SmokeLog, '', $Utf8NoBom)

function Write-SmokeLog([string]$Message) {
    $line = "[{0}] {1}" -f ([DateTime]::UtcNow.ToString('o')), $Message
    [IO.File]::AppendAllText($SmokeLog, $line + [Environment]::NewLine, $script:Utf8NoBom)
    Write-Host $line
}

function Format-NativeArgument([string]$Value) {
    if ($null -eq $Value) { return '""' }
    if ($Value.Contains('"')) {
        throw 'Native Prozessargumente dürfen keine eingebetteten Anführungszeichen enthalten.'
    }

    # Command switches must remain unquoted. Quoting every token turns /i, /qn and
    # /L*V! into "/i", "/qn" and "/L*V!". msiexec can interpret that as an
    # invalid command line and wait on a hidden usage dialog without creating a log.
    # Quote only values containing whitespace, notably file-system paths.
    if ($Value -notmatch '\s') { return $Value }
    return '"' + $Value + '"'
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
        [ValidateRange(1, 900)][int]$TimeoutSeconds = 180,
        [string]$ExpectedLogPath = '',
        [ValidateRange(1, 60)][int]$StartupLogTimeoutSeconds = 15
    )

    $argumentLine = ($Arguments | ForEach-Object { Format-NativeArgument $_ }) -join ' '
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

        if (-not [string]::IsNullOrWhiteSpace($ExpectedLogPath)) {
            $logDeadline = [DateTime]::UtcNow.AddSeconds($StartupLogTimeoutSeconds)
            while (-not $process.HasExited -and
                   -not (Test-Path -LiteralPath $ExpectedLogPath -PathType Leaf) -and
                   [DateTime]::UtcNow -lt $logDeadline) {
                Start-Sleep -Milliseconds 200
            }
            if (-not $process.HasExited -and
                -not (Test-Path -LiteralPath $ExpectedLogPath -PathType Leaf)) {
                Write-SmokeLog "NO LOG: $Description did not create $ExpectedLogPath within $StartupLogTimeoutSeconds seconds."
                $childProcessId = $process.Id
                Stop-ProcessTree -ProcessId $childProcessId
                throw "$Description hat kein Windows-Installer-Protokoll angelegt. Die msiexec-Befehlszeile wurde wahrscheinlich nicht akzeptiert. Details: $SmokeLog"
            }
        }

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

function Normalize-WindowsPath {
    param(
        [string]$Value,
        [switch]$Directory
    )

    if ([string]::IsNullOrWhiteSpace($Value)) {
        return ''
    }

    $expanded = [Environment]::ExpandEnvironmentVariables($Value.Trim().Trim('"'))
    try {
        $normalized = [IO.Path]::GetFullPath($expanded)
    } catch {
        $normalized = $expanded
    }

    if ($Directory) {
        return $normalized.TrimEnd([IO.Path]::DirectorySeparatorChar, [IO.Path]::AltDirectorySeparatorChar)
    }
    return $normalized
}

function Release-ComObject([object]$Value) {
    if ($null -ne $Value -and [Runtime.InteropServices.Marshal]::IsComObject($Value)) {
        [void][Runtime.InteropServices.Marshal]::FinalReleaseComObject($Value)
    }
}

function Get-ShortcutMetadata {
    param([Parameter(Mandatory = $true)][string]$ShortcutPath)

    $targetPath = ''
    $workingDirectory = ''
    $wscript = $null
    $shortcut = $null
    try {
        $wscript = New-Object -ComObject WScript.Shell
        $shortcut = $wscript.CreateShortcut($ShortcutPath)
        $targetPath = [string]$shortcut.TargetPath
        $workingDirectory = [string]$shortcut.WorkingDirectory
        Write-SmokeLog "SHORTCUT WScript target: '$targetPath'"
        Write-SmokeLog "SHORTCUT WScript working directory: '$workingDirectory'"
    } catch {
        Write-SmokeLog "WARN: WScript.Shell konnte die Desktopverknüpfung nicht auslesen: $($_.Exception.Message)"
    } finally {
        Release-ComObject $shortcut
        Release-ComObject $wscript
    }

    # Shell.Application can resolve MSI-created links on systems where WScript.Shell
    # returns an empty TargetPath. This is common on minimal CI desktop sessions.
    if ([string]::IsNullOrWhiteSpace($targetPath)) {
        $shellApplication = $null
        $folder = $null
        $item = $null
        $link = $null
        try {
            $shellApplication = New-Object -ComObject Shell.Application
            $folder = $shellApplication.Namespace((Split-Path -Parent $ShortcutPath))
            if ($null -ne $folder) {
                $item = $folder.ParseName((Split-Path -Leaf $ShortcutPath))
            }
            if ($null -ne $item) {
                $link = $item.GetLink
            }
            if ($null -ne $link) {
                $targetPath = [string]$link.Path
                $workingDirectory = [string]$link.WorkingDirectory
                Write-SmokeLog "SHORTCUT Shell.Application target: '$targetPath'"
                Write-SmokeLog "SHORTCUT Shell.Application working directory: '$workingDirectory'"
            }
        } catch {
            Write-SmokeLog "WARN: Shell.Application konnte die Desktopverknüpfung nicht auslesen: $($_.Exception.Message)"
        } finally {
            Release-ComObject $link
            Release-ComObject $item
            Release-ComObject $folder
            Release-ComObject $shellApplication
        }
    }

    return [PSCustomObject]@{
        TargetPath = $targetPath
        WorkingDirectory = $workingDirectory
    }
}

function Assert-DesktopShortcut {
    Write-SmokeLog 'VERIFY: common desktop shortcut'

    # Explorer and Windows Installer can publish the link a fraction after msiexec
    # returns. Give the filesystem a short bounded settling period.
    $shortcutDeadline = [DateTime]::UtcNow.AddSeconds(10)
    while (-not (Test-Path -LiteralPath $DesktopShortcutPath -PathType Leaf) -and
           [DateTime]::UtcNow -lt $shortcutDeadline) {
        Start-Sleep -Milliseconds 200
    }
    if (-not (Test-Path -LiteralPath $DesktopShortcutPath -PathType Leaf)) {
        throw "Desktopverknüpfung fehlt: $DesktopShortcutPath"
    }

    $expectedTarget = Normalize-WindowsPath (Join-Path $InstallRoot 'AstroFocusStudio.exe')
    $expectedWorkingDirectory = Normalize-WindowsPath $InstallRoot -Directory
    $metadata = Get-ShortcutMetadata -ShortcutPath $DesktopShortcutPath
    $actualTarget = Normalize-WindowsPath ([string]$metadata.TargetPath)
    $actualWorkingDirectory = Normalize-WindowsPath ([string]$metadata.WorkingDirectory) -Directory

    if ([string]::IsNullOrWhiteSpace($actualTarget)) {
        throw "Desktopverknüpfung wurde angelegt, ihr Ziel konnte aber nicht ausgelesen werden: $DesktopShortcutPath"
    }
    if (-not $actualTarget.Equals($expectedTarget, [StringComparison]::OrdinalIgnoreCase)) {
        throw "Desktopverknüpfung verweist auf ein falsches Ziel: '$actualTarget' statt '$expectedTarget'"
    }

    # WiX authoring is checked statically for WorkingDirectory=INSTALLFOLDER. Some
    # CI shell APIs return an empty working directory for a valid MSI-created link.
    # A non-empty runtime value must still match after trimming trailing separators.
    if ([string]::IsNullOrWhiteSpace($actualWorkingDirectory)) {
        Write-SmokeLog 'WARN: Das Arbeitsverzeichnis der Desktopverknüpfung wurde von der CI-Shell-API nicht zurückgegeben.'
    } elseif (-not $actualWorkingDirectory.Equals($expectedWorkingDirectory, [StringComparison]::OrdinalIgnoreCase)) {
        throw "Desktopverknüpfung besitzt ein falsches Arbeitsverzeichnis: '$actualWorkingDirectory' statt '$expectedWorkingDirectory'"
    }

    Write-SmokeLog 'PASS: common desktop shortcut exists and resolves to AstroFocusStudio.exe'
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
    $shortcutDeadline = [DateTime]::UtcNow.AddSeconds(5)
    while ((Test-Path -LiteralPath $DesktopShortcutPath -PathType Leaf) -and
           [DateTime]::UtcNow -lt $shortcutDeadline) {
        Start-Sleep -Milliseconds 200
    }
    if (Test-Path -LiteralPath $DesktopShortcutPath -PathType Leaf) {
        throw "Nach der Deinstallation ist die Desktopverknüpfung noch vorhanden: $DesktopShortcutPath"
    }
    Write-SmokeLog 'PASS: product and desktop shortcut removed'
}

function Invoke-HealthCheck {
    # Test the two device hosts directly before the engine. The engine health check is
    # intentionally a self-check and no longer starts nested host processes. This makes
    # every failing component visible through its own executable name and exit code.
    $programs = @(
        (Join-Path $InstallRoot 'AstroFocusCameraHost.exe'),
        (Join-Path $InstallRoot 'AstroFocusFocuserHost.exe'),
        (Join-Path $InstallRoot 'AstroFocusEngine.exe')
    )
    foreach ($program in $programs) {
        Invoke-InstallerProcess `
            -FilePath $program `
            -Arguments @('--health-check') `
            -Description "Health-Check $([IO.Path]::GetFileName($program))" `
            -SuccessExitCodes @(0) `
            -TimeoutSeconds 30
    }
}

function Copy-FrontendDiagnostics {
    param(
        [Parameter(Mandatory = $true)][DateTime]$StartedAt,
        [switch]$IncludeEventLog
    )

    $localAppData = [Environment]::GetFolderPath([Environment+SpecialFolder]::LocalApplicationData)
    if (-not [string]::IsNullOrWhiteSpace($localAppData)) {
        $sourceTrace = Join-Path $localAppData 'AstroFocusStudio\Logs\FrontendTrace.log'
        if (Test-Path -LiteralPath $sourceTrace -PathType Leaf) {
            Copy-Item -LiteralPath $sourceTrace -Destination (Join-Path $LogRoot 'frontend-trace.log') -Force -ErrorAction SilentlyContinue
        }
    }

    if ($IncludeEventLog) {
        try {
            $events = Get-WinEvent -FilterHashtable @{ LogName = 'Application'; StartTime = $StartedAt } -ErrorAction Stop |
                Where-Object {
                    ($_.ProviderName -eq 'Application Error' -or $_.ProviderName -eq 'Windows Error Reporting') -and
                    ($_.Message -match 'AstroFocusStudio\.exe')
                } |
                Select-Object TimeCreated, ProviderName, Id, LevelDisplayName, Message
            if ($events) {
                $events | Format-List * | Out-File -LiteralPath (Join-Path $LogRoot 'frontend-application-events.log') -Encoding utf8
            }
        } catch {
            Write-SmokeLog "WARN: Windows-Anwendungsereignisse konnten nicht gelesen werden: $($_.Exception.Message)"
        }
    }
}

function Invoke-FrontendStartupCheck {
    $program = Join-Path $InstallRoot 'AstroFocusStudio.exe'
    if (-not (Test-Path -LiteralPath $program -PathType Leaf)) {
        throw "Frontend fehlt: $program"
    }

    $startedAt = [DateTime]::Now.AddSeconds(-2)
    $localAppData = [Environment]::GetFolderPath([Environment+SpecialFolder]::LocalApplicationData)
    if (-not [string]::IsNullOrWhiteSpace($localAppData)) {
        Remove-Item -LiteralPath (Join-Path $localAppData 'AstroFocusStudio\Logs\FrontendTrace.log') -Force -ErrorAction SilentlyContinue
    }

    Write-SmokeLog 'START: Frontend-GUI-Startprüfung'
    Write-SmokeLog "COMMAND: $program"
    $startInfo = New-Object System.Diagnostics.ProcessStartInfo
    $startInfo.FileName = $program
    $startInfo.WorkingDirectory = $InstallRoot
    $startInfo.UseShellExecute = $false
    $startInfo.CreateNoWindow = $false
    $process = New-Object System.Diagnostics.Process
    $process.StartInfo = $startInfo
    $passed = $false
    $started = $false
    try {
        if (-not $process.Start()) {
            throw 'AstroFocusStudio.exe konnte nicht gestartet werden.'
        }
        $started = $true
        Write-SmokeLog "Frontend PID: $($process.Id)"
        $deadline = [DateTime]::UtcNow.AddSeconds(25)
        $windowFound = $false
        while ([DateTime]::UtcNow -lt $deadline) {
            if ($process.HasExited) {
                $process.WaitForExit()
                Copy-FrontendDiagnostics -StartedAt $startedAt -IncludeEventLog
                throw "AstroFocusStudio.exe wurde während des Starts beendet (Exitcode $($process.ExitCode))."
            }
            $process.Refresh()
            if ($process.MainWindowHandle -ne [IntPtr]::Zero -and $process.MainWindowTitle -like 'AstroFocus Studio 3.9.0*') {
                $windowFound = $true
                break
            }
            Start-Sleep -Milliseconds 250
        }
        if (-not $windowFound) {
            Copy-FrontendDiagnostics -StartedAt $startedAt -IncludeEventLog
            Stop-ProcessTree -ProcessId $process.Id
            throw 'Das Hauptfenster erschien nicht innerhalb von 25 Sekunden.'
        }

        Write-SmokeLog "PASS: Frontend window visible: '$($process.MainWindowTitle)' (handle $($process.MainWindowHandle))"
        # The visible window deliberately starts the local engine after it is shown.
        # Give this bounded startup handshake time to finish instead of sampling the
        # temporary busy state at one arbitrary three-second point.
        $responsiveDeadline = [DateTime]::UtcNow.AddSeconds(15)
        $responsive = $false
        while ([DateTime]::UtcNow -lt $responsiveDeadline) {
            if ($process.HasExited) {
                $process.WaitForExit()
                Copy-FrontendDiagnostics -StartedAt $startedAt -IncludeEventLog
                throw "AstroFocusStudio.exe wurde kurz nach dem sichtbaren Start beendet (Exitcode $($process.ExitCode))."
            }
            $process.Refresh()
            if ($process.Responding) {
                $responsive = $true
                break
            }
            Start-Sleep -Milliseconds 250
        }
        if (-not $responsive) {
            Copy-FrontendDiagnostics -StartedAt $startedAt -IncludeEventLog
            Stop-ProcessTree -ProcessId $process.Id
            throw 'Das sichtbare AstroFocus-Hauptfenster reagierte nach dem begrenzten Engine-Startfenster nicht.'
        }
        Start-Sleep -Seconds 2
        if ($process.HasExited) {
            $process.WaitForExit()
            Copy-FrontendDiagnostics -StartedAt $startedAt -IncludeEventLog
            throw "AstroFocusStudio.exe wurde nach dem erfolgreichen sichtbaren Start beendet (Exitcode $($process.ExitCode))."
        }

        Write-SmokeLog 'CLOSE: request graceful frontend shutdown'
        if (-not $process.CloseMainWindow()) {
            Copy-FrontendDiagnostics -StartedAt $startedAt -IncludeEventLog
            Stop-ProcessTree -ProcessId $process.Id
            throw 'WM_CLOSE konnte nicht an das Hauptfenster gesendet werden.'
        }
        if (-not $process.WaitForExit(15000)) {
            Copy-FrontendDiagnostics -StartedAt $startedAt -IncludeEventLog
            Stop-ProcessTree -ProcessId $process.Id
            throw 'Das Frontend wurde nach WM_CLOSE nicht innerhalb von 15 Sekunden beendet.'
        }
        $process.WaitForExit()
        if ($process.ExitCode -ne 0) {
            Copy-FrontendDiagnostics -StartedAt $startedAt -IncludeEventLog
            throw "Das Frontend beendete den normalen Fensterschluss mit Exitcode $($process.ExitCode)."
        }
        $passed = $true
        Write-SmokeLog 'PASS: Frontend starts, stays responsive and closes cleanly'
    } finally {
        if (-not $passed) {
            Copy-FrontendDiagnostics -StartedAt $startedAt -IncludeEventLog
        } else {
            Copy-FrontendDiagnostics -StartedAt $startedAt
        }
        if ($started -and -not $process.HasExited) {
            Stop-ProcessTree -ProcessId $process.Id
        }
        $process.Dispose()
        Start-Sleep -Seconds 1
        $remainingEngine = @(Get-Process -Name 'AstroFocusEngine' -ErrorAction SilentlyContinue)
        foreach ($engine in $remainingEngine) {
            Write-SmokeLog "WARN: frontend shutdown left engine PID $($engine.Id); stopping it before installer repair."
            Stop-Process -Id $engine.Id -Force -ErrorAction SilentlyContinue
        }
    }
}

function Stop-AstroFocusProcesses {
    $names = @(
        'AstroFocusStudio',
        'AstroFocusEngine',
        'AstroFocusCameraHost',
        'AstroFocusFocuserHost',
        'AstroFocusFocuserSetup',
        'AstroFocusUpdater',
        'AstroFocusSetup'
    )
    foreach ($name in $names) {
        $processes = @(Get-Process -Name $name -ErrorAction SilentlyContinue)
        foreach ($process in $processes) {
            Write-SmokeLog "CLEANUP: stopping $($process.ProcessName) PID $($process.Id)"
            Stop-Process -Id $process.Id -Force -ErrorAction SilentlyContinue
        }
    }
}

function Invoke-CleanupUninstall {
    Stop-AstroFocusProcesses
    Start-Sleep -Seconds 2

    if ($Mode -eq 'Bundle') {
        if (-not (Test-Path -LiteralPath $InstallRoot)) { return }
        try {
            Invoke-InstallerProcess `
                -FilePath $BundlePath `
                -Arguments @('/uninstall', '/quiet', '/norestart', '/log', (Join-Path $LogRoot 'cleanup-bundle-uninstall.log')) `
                -Description 'Bereinigungs-Bundle-Deinstallation' `
                -SuccessExitCodes @(0, 1605, 1614, 1641, 3010) `
                -TimeoutSeconds 90
        } catch {
            Write-Warning $_
            Write-SmokeLog "WARN: bundle cleanup failed: $($_.Exception.Message)"
        }
        return
    }

    # The raw MSI test runs on a separate fresh Windows runner. It must therefore be
    # cleaned up directly with msiexec and must not involve the Burn registration.
    if (-not (Test-Path -LiteralPath $InstallRoot)) { return }
    try {
        Invoke-InstallerProcess `
            -FilePath $MsiExecPath `
            -Arguments @('/x', $MsiPath, '/qn', '/norestart', '/L*V!', (Join-Path $LogRoot 'cleanup-msi-uninstall.log'), 'REBOOT=ReallySuppress') `
            -Description 'Bereinigungs-MSI-Deinstallation' `
            -ExpectedLogPath (Join-Path $LogRoot 'cleanup-msi-uninstall.log') `
            -SuccessExitCodes @(0, 1605, 1614, 1641, 3010) `
            -TimeoutSeconds 90
    } catch {
        Write-Warning $_
        Write-SmokeLog "WARN: MSI cleanup failed: $($_.Exception.Message)"
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

Write-SmokeLog "Installer smoke test started for AstroFocus Studio $ProductVersion in $Mode mode"
try {
    if ($Mode -eq 'Bundle') {
        # Burn bundle: install, verify every payload hash, exercise repair, then uninstall.
        # This mode runs on its own clean GitHub-hosted Windows runner.
        Invoke-InstallerProcess -FilePath $BundlePath -Arguments @('/quiet', '/norestart', '/log', $bundleInstallLog) -Description 'Bundle-Installation' -TimeoutSeconds 180
        Assert-InstalledPayload
        Assert-DesktopShortcut
        Invoke-HealthCheck
        Invoke-FrontendStartupCheck

        $repairProbe = Join-Path $InstallRoot 'AstroFocusFocuserHost.exe'
        Remove-Item -LiteralPath $repairProbe -Force
        if (Test-Path -LiteralPath $repairProbe) {
            throw 'Die Reparatur-Testdatei konnte nicht entfernt werden.'
        }
        Invoke-InstallerProcess -FilePath $BundlePath -Arguments @('/repair', '/quiet', '/norestart', '/log', $bundleRepairLog) -Description 'Bundle-Reparatur' -TimeoutSeconds 180
        Assert-InstalledPayload
        Assert-DesktopShortcut

        Invoke-InstallerProcess -FilePath $BundlePath -Arguments @('/uninstall', '/quiet', '/norestart', '/log', $bundleUninstallLog) -Description 'Bundle-Deinstallation' -TimeoutSeconds 180
        Assert-Uninstalled
        Write-SmokeLog 'PASS: Bundle install, repair, health checks and uninstall'
        Write-Host 'Bundle-Installation, Reparatur, Health-Checks und Deinstallation wurden bestanden.'
    } else {
        # Raw MSI: independently prove install, repair and removal on a fresh runner.
        # Never run this immediately after a Burn transaction on the same Windows VM:
        # Burn can leave Windows Installer restart/transaction state behind even when
        # the bundle itself returns exit code 0.
        Invoke-InstallerProcess -FilePath $MsiExecPath -Arguments @('/i', $MsiPath, '/qn', '/norestart', '/L*V!', $msiInstallLog, 'REBOOT=ReallySuppress') -Description 'MSI-Installation' -ExpectedLogPath $msiInstallLog -TimeoutSeconds 180
        Assert-InstalledPayload
        Assert-DesktopShortcut
        Invoke-HealthCheck
        Invoke-FrontendStartupCheck

        $repairProbe = Join-Path $InstallRoot 'AstroFocusFocuserHost.exe'
        Remove-Item -LiteralPath $repairProbe -Force
        if (Test-Path -LiteralPath $repairProbe) {
            throw 'Die MSI-Reparatur-Testdatei konnte nicht entfernt werden.'
        }
        $msiRepairLog = Join-Path $LogRoot 'msi-repair.log'
        Invoke-InstallerProcess -FilePath $MsiExecPath -Arguments @('/fa', $MsiPath, '/qn', '/norestart', '/L*V!', $msiRepairLog, 'REBOOT=ReallySuppress') -Description 'MSI-Reparatur' -ExpectedLogPath $msiRepairLog -TimeoutSeconds 180
        Assert-InstalledPayload
        Assert-DesktopShortcut

        Invoke-InstallerProcess -FilePath $MsiExecPath -Arguments @('/x', $MsiPath, '/qn', '/norestart', '/L*V!', $msiUninstallLog, 'REBOOT=ReallySuppress') -Description 'MSI-Deinstallation' -ExpectedLogPath $msiUninstallLog -TimeoutSeconds 180
        Assert-Uninstalled
        Write-SmokeLog 'PASS: MSI install, repair, health checks and uninstall'
        Write-Host 'MSI-Installation, Reparatur, Health-Checks und Deinstallation wurden bestanden.'
    }
} catch {
    Write-SmokeLog "FAIL: $($_.Exception.Message)"
    throw
} finally {
    Invoke-CleanupUninstall
}
