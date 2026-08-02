[CmdletBinding()]
param(
    [ValidateSet('Install','Repair','Uninstall','Rollback','Health')]
    [string]$Mode = 'Install',
    [string]$Source = '',
    [switch]$Quiet,
    [switch]$NoElevation,
    [switch]$AllowUnsignedDevelopment,
    [switch]$InternalRelocated,
    [int]$WaitForProcessId = 0
)
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'
$ScriptDirectory = $PSScriptRoot
if ([string]::IsNullOrWhiteSpace($ScriptDirectory) -and -not [string]::IsNullOrWhiteSpace([string]$MyInvocation.MyCommand.Path)) {
    $ScriptDirectory = Split-Path -Parent $MyInvocation.MyCommand.Path
}
if ([string]::IsNullOrWhiteSpace($ScriptDirectory)) {
    throw 'Der Verzeichnisort des Setupskripts konnte nicht bestimmt werden.'
}
if ([string]::IsNullOrWhiteSpace($Source)) {
    $Source = Join-Path -Path $ScriptDirectory -ChildPath 'payload'
}
$ProductName = 'AstroFocus Studio'
$Version = '3.8.8'
$InstallRoot = Join-Path $env:ProgramFiles $ProductName
$AdminDataRoot = Join-Path $env:ProgramData 'AstroFocusStudio'
$RollbackRoot = Join-Path $AdminDataRoot 'InstallerRollback'
$StatePath = Join-Path $AdminDataRoot 'install-state.json'
$LogRoot = Join-Path $AdminDataRoot 'Logs'
$LogPath = Join-Path $LogRoot 'Installer.log'
$DevMarkerName = 'UNSIGNED_DEVELOPMENT_BUILD.txt'
# Replace with the SHA-256 of update-public-key.cer before signing a production release.
$PinnedUpdateCertificateSha256 = 'REPLACE_WITH_UPDATE_CERTIFICATE_SHA256'
$RequiredFiles = @(
    'AstroFocusStudio.exe','AstroFocusEngine.exe','AstroFocusCameraHost.exe',
    'AstroFocusFocuserHost.exe','AstroFocusFocuserSetup.exe','AstroFocusUpdater.exe',
    'AstroFocusUpdater.ps1','AstroFocusSetup.exe','AstroFocusSetup.ps1',
    'update-public-key.cer','release-manifest.json'
)

function Show-InstallerMessage([string]$Message,[switch]$ErrorIcon) {
    if ($Quiet) { return }
    try {
        Add-Type -AssemblyName System.Windows.Forms -ErrorAction Stop
        $icon = if ($ErrorIcon) { [System.Windows.Forms.MessageBoxIcon]::Error } else { [System.Windows.Forms.MessageBoxIcon]::Information }
        [System.Windows.Forms.MessageBox]::Show(
            $Message,
            "$ProductName Setup",
            [System.Windows.Forms.MessageBoxButtons]::OK,
            $icon
        ) | Out-Null
    } catch {
        if ($ErrorIcon) { Write-Error $Message -ErrorAction Continue } else { Write-Host $Message }
    }
}
function Get-ModeSuccessMessage {
    switch ($Mode) {
        'Install' { return "$ProductName $Version wurde erfolgreich installiert.`n`nStarten Sie das Programm über das Startmenü." }
        'Repair' { return "$ProductName $Version wurde erfolgreich repariert." }
        'Uninstall' { return "$ProductName wurde erfolgreich deinstalliert.`n`nBenutzerdaten und Diagnoseprotokolle wurden beibehalten." }
        'Rollback' { return 'Die vorherige AstroFocus-Version wurde erfolgreich wiederhergestellt.' }
        'Health' { return 'Die AstroFocus-Installation wurde erfolgreich geprüft.' }
    }
}
function Clear-DevelopmentZoneIdentifiers([string]$Payload) {
    if (-not (Test-DevelopmentModeAllowed) -or -not (Test-PayloadDevelopmentMarker $Payload)) { return }
    foreach ($root in @($ScriptDirectory,$Payload) | Select-Object -Unique) {
        if (-not (Test-Path -LiteralPath $root)) { continue }
        Get-ChildItem -LiteralPath $root -File -Recurse -Force -ErrorAction SilentlyContinue |
            ForEach-Object { try { Unblock-File -LiteralPath $_.FullName -ErrorAction Stop } catch {} }
    }
}

function Enter-MaintenanceMutex {
    try {
        $script:MaintenanceMutex = [System.Threading.Mutex]::new($false,'Global\AstroFocusStudio.Maintenance')
        if (-not $script:MaintenanceMutex.WaitOne(0)) { throw 'Eine AstroFocus-Installation oder ein Update läuft bereits.' }
    } catch [System.Threading.AbandonedMutexException] {
        Write-InstallLog 'Verwaiste gemeinsame Wartungssperre übernommen.'
    } catch [System.UnauthorizedAccessException] {
        throw 'Eine AstroFocus-Installation oder ein Update läuft bereits oder die gemeinsame Wartungssperre ist nicht zugänglich.'
    }
}
function Enter-InstallerMutex {
    $script:InstallerMutex = [System.Threading.Mutex]::new($false,'Global\AstroFocusStudio.Installer')
    try {
        if (-not $script:InstallerMutex.WaitOne(0)) { throw 'Eine andere AstroFocus-Installation, Reparatur oder Deinstallation läuft bereits.' }
    } catch [System.Threading.AbandonedMutexException] {
        Write-InstallLog 'Verwaiste Installer-Sperre übernommen.'
    }
}
function Write-InstallLog([string]$Message) {
    New-Item -ItemType Directory -Force -Path $LogRoot | Out-Null
    Add-Content -LiteralPath $LogPath -Encoding UTF8 -Value ("{0:o} | {1}" -f [DateTime]::UtcNow,$Message)
}
function Test-Administrator {
    $identity = [Security.Principal.WindowsIdentity]::GetCurrent()
    $principal = [Security.Principal.WindowsPrincipal]::new($identity)
    return $principal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}
function Test-IsWithin([string]$Child,[string]$Parent) {
    $childFull = [IO.Path]::GetFullPath($Child).TrimEnd('\')
    $parentFull = [IO.Path]::GetFullPath($Parent).TrimEnd('\')
    return $childFull.Equals($parentFull,[StringComparison]::OrdinalIgnoreCase) -or $childFull.StartsWith($parentFull + '\',[StringComparison]::OrdinalIgnoreCase)
}
function Test-IsReparsePoint([string]$Path) {
    $item = Get-Item -LiteralPath $Path -Force
    return (($item.Attributes -band [IO.FileAttributes]::ReparsePoint) -ne 0)
}
function Start-RelocatedDestructiveMode {
    if ($InternalRelocated -or $Mode -notin @('Install','Repair','Uninstall','Rollback')) { return }
    if (-not (Test-IsWithin $ScriptDirectory $InstallRoot)) { return }
    $tempRoot = Join-Path $env:TEMP ("AstroFocusSetup-{0}" -f [Guid]::NewGuid().ToString('N'))
    New-Item -ItemType Directory -Force -Path $tempRoot | Out-Null
    foreach ($name in @('AstroFocusSetup.exe','AstroFocusSetup.ps1',$DevMarkerName)) {
        $from = Join-Path $ScriptDirectory $name
        if (Test-Path -LiteralPath $from -PathType Leaf) { Copy-Item -LiteralPath $from -Destination (Join-Path $tempRoot $name) -Force }
    }
    $launcher = Join-Path $tempRoot 'AstroFocusSetup.exe'
    if (-not (Test-Path -LiteralPath $launcher -PathType Leaf)) { throw 'Das Setup konnte für die sichere Selbstentfernung nicht in den Temp-Ordner kopiert werden.' }
    $arguments = @('-Mode',$Mode,'-Source',('"{0}"' -f $Source),'-Quiet','-InternalRelocated','-WaitForProcessId',$PID)
    if ($AllowUnsignedDevelopment) { $arguments += '-AllowUnsignedDevelopment' }
    Start-Process -FilePath $launcher -ArgumentList $arguments | Out-Null
    exit 0
}
function Wait-ForPreviousInstance {
    if ($WaitForProcessId -le 0) { return }
    try { Wait-Process -Id $WaitForProcessId -Timeout 30 -ErrorAction SilentlyContinue } catch {}
    Start-Sleep -Milliseconds 800
}
function Request-Elevation {
    if ($NoElevation -or (Test-Administrator)) { return }
    $launcher = Join-Path $ScriptDirectory 'AstroFocusSetup.exe'
    if (-not (Test-Path -LiteralPath $launcher -PathType Leaf)) { throw 'AstroFocusSetup.exe fehlt; Administratorrechte sind erforderlich.' }
    $arguments = @('-Mode',$Mode,'-Source',('"{0}"' -f $Source),'-Quiet')
    if ($InternalRelocated) { $arguments += '-InternalRelocated' }
    if ($AllowUnsignedDevelopment) { $arguments += '-AllowUnsignedDevelopment' }
    try {
        $process = Start-Process -FilePath $launcher -ArgumentList $arguments -Verb RunAs -Wait -PassThru
    } catch {
        throw "Die Administratorfreigabe konnte nicht gestartet werden: $($_.Exception.Message)"
    }
    if ($process.ExitCode -eq 0) {
        Show-InstallerMessage (Get-ModeSuccessMessage)
    } else {
        Show-InstallerMessage ("Das Setup wurde mit Exitcode {0} beendet.`n`nDetails: {1}" -f $process.ExitCode,$LogPath) -ErrorIcon
    }
    exit $process.ExitCode
}
function Stop-AstroFocusProcesses {
    foreach ($name in @('AstroFocusStudio','AstroFocusEngine','AstroFocusCameraHost','AstroFocusFocuserHost','AstroFocusFocuserSetup','AstroFocusUpdater')) {
        foreach ($process in @(Get-Process -Name $name -ErrorAction SilentlyContinue)) {
            $path = $null
            try { $path = $process.Path } catch {}
            if ([string]::IsNullOrWhiteSpace($path) -or -not (Test-IsWithin $path $InstallRoot)) {
                Write-InstallLog "Prozess $name/$($process.Id) außerhalb des Installationsordners wurde nicht beendet."
                continue
            }
            try {
                $process.CloseMainWindow() | Out-Null
                if (-not $process.WaitForExit(3000)) { Stop-Process -Id $process.Id -Force }
            } catch { try { Stop-Process -Id $process.Id -Force -ErrorAction SilentlyContinue } catch {} }
        }
    }
}
function Test-SafeWindowsRelativePath([string]$Relative,[string]$Context) {
    if ([string]::IsNullOrWhiteSpace($Relative) -or [IO.Path]::IsPathRooted($Relative) -or $Relative.Contains(':')) { throw "Ungültiger $Context-Pfad: $Relative" }
    $normal = $Relative.Replace('/','\')
    $trimmed = $normal.TrimEnd('\')
    if ([string]::IsNullOrWhiteSpace($trimmed)) { throw "Leerer $Context-Pfad." }
    foreach ($segment in $trimmed.Split('\')) {
        if ([string]::IsNullOrWhiteSpace($segment) -or $segment -eq '.' -or $segment -eq '..' -or $segment.EndsWith('.') -or $segment.EndsWith(' ')) { throw "Unsicherer $Context-Pfad: $Relative" }
        if ($segment -match '^(?i:CON|PRN|AUX|NUL|COM[1-9]|LPT[1-9])(?:\..*)?$') { throw "Reservierter Windows-Name im $Context-Pfad: $Relative" }
    }
    return $normal
}
function Resolve-ManifestEntry([string]$Root,[string]$Relative) {
    $normal = Test-SafeWindowsRelativePath $Relative 'Manifest'
    $rootFull = [IO.Path]::GetFullPath($Root).TrimEnd('\')
    $full = [IO.Path]::GetFullPath((Join-Path $rootFull $normal))
    if (-not $full.StartsWith($rootFull + '\',[StringComparison]::OrdinalIgnoreCase)) { throw "Manifestpfad verlässt den Payload-Ordner: $Relative" }
    return $full
}
function Test-ManifestAndFiles([string]$Payload,[string]$ExpectedVersion = '') {
    if (-not (Test-Path -LiteralPath $Payload -PathType Container)) { throw "Payload-Ordner fehlt: $Payload" }
    if (Test-IsReparsePoint $Payload) { throw 'Payload-Ordner darf kein Reparse Point sein.' }
    $payloadFull = [IO.Path]::GetFullPath($Payload).TrimEnd('\')
    $manifestPath = Join-Path $payloadFull 'release-manifest.json'
    if (-not (Test-Path -LiteralPath $manifestPath -PathType Leaf)) { throw 'release-manifest.json fehlt.' }
    if (Test-IsReparsePoint $manifestPath) { throw 'release-manifest.json darf kein Reparse Point sein.' }
    $manifest = Get-Content -LiteralPath $manifestPath -Raw -Encoding UTF8 | ConvertFrom-Json
    if ($manifest.product -ne $ProductName) { throw 'Das Payload-Manifest gehört zu einem anderen Produkt.' }
    if (-not [string]::IsNullOrWhiteSpace($ExpectedVersion) -and [string]$manifest.version -ne $ExpectedVersion) { throw 'Version des Payload-Manifests stimmt nicht.' }
    if ($manifest.PSObject.Properties.Name -contains 'architecture' -and [string]$manifest.architecture -ne 'windows-x64') { throw 'Das Payload besitzt nicht die erwartete Windows-x64-Architektur.' }
    $entries = @($manifest.files)
    if ($entries.Count -eq 0) { throw 'Das Payload-Manifest enthält keine Dateien.' }
    $seen = [Collections.Generic.HashSet[string]]::new([StringComparer]::OrdinalIgnoreCase)
    foreach ($entry in $entries) {
        $relative = [string]$entry.path
        if ([string]$entry.sha256 -notmatch '^[0-9a-fA-F]{64}$') { throw "Ungültiger SHA-256-Wert im Manifest: $relative" }
        $path = Resolve-ManifestEntry $payloadFull $relative
        $canonicalRelative = $path.Substring($payloadFull.Length).TrimStart('\').Replace('\','/')
        if (-not $seen.Add($canonicalRelative)) { throw "Doppelter oder aliasierter Manifestpfad: $relative" }
        if (-not (Test-Path -LiteralPath $path -PathType Leaf)) { throw "Manifestdatei fehlt: $relative" }
        if (Test-IsReparsePoint $path) { throw "Manifestdatei darf kein Reparse Point sein: $relative" }
        $item = Get-Item -LiteralPath $path -Force
        if ($entry.PSObject.Properties.Name -notcontains 'size' -or [int64]$entry.size -ne $item.Length) { throw "Dateigröße stimmt nicht: $relative" }
        $actual = (Get-FileHash -Algorithm SHA256 -LiteralPath $path).Hash.ToLowerInvariant()
        if ($actual -ne ([string]$entry.sha256).ToLowerInvariant()) { throw "SHA-256-Prüfung fehlgeschlagen: $relative" }
    }
    $actualFiles = @(Get-ChildItem -LiteralPath $payloadFull -File -Recurse -Force | Where-Object { $_.FullName -ne $manifestPath })
    foreach ($file in $actualFiles) {
        if (Test-IsReparsePoint $file.FullName) { throw "Payloaddatei darf kein Reparse Point sein: $($file.FullName)" }
        $relative = $file.FullName.Substring($payloadFull.Length).TrimStart('\').Replace('\','/')
        if (-not $seen.Contains($relative)) { throw "Nicht im Manifest aufgeführte Payloaddatei: $relative" }
    }
    if ($actualFiles.Count -ne $seen.Count) { throw 'Manifest und Payload enthalten unterschiedlich viele Dateien.' }
    return $manifest
}
function Test-Payload([string]$Payload) {
    foreach ($file in $RequiredFiles) {
        if (-not (Test-Path -LiteralPath (Join-Path $Payload $file) -PathType Leaf)) { throw "Erforderliche Installationsdatei fehlt: $file" }
    }
    return Test-ManifestAndFiles $Payload $Version
}
function Test-DevelopmentModeAllowed {
    return $AllowUnsignedDevelopment -and (Test-Path -LiteralPath (Join-Path $ScriptDirectory $DevMarkerName) -PathType Leaf)
}
function Test-PayloadDevelopmentMarker([string]$Payload) {
    return Test-Path -LiteralPath (Join-Path $Payload $DevMarkerName) -PathType Leaf
}
function Test-PayloadSignatures([string]$Payload) {
    $setupPath = Join-Path $ScriptDirectory 'AstroFocusSetup.exe'
    if (-not (Test-Path -LiteralPath $setupPath -PathType Leaf)) { throw 'AstroFocusSetup.exe fehlt.' }
    $setupSignature = Get-AuthenticodeSignature -LiteralPath $setupPath
    if ($setupSignature.Status -ne 'Valid') {
        if (-not (Test-DevelopmentModeAllowed) -or -not (Test-PayloadDevelopmentMarker $Payload)) {
            throw 'Das Setup oder Payload ist nicht gültig signiert. Unsignierte Builds benötigen Markierungen am Bundle und im Payload.'
        }
        Write-InstallLog 'WARNUNG: ausdrücklich freigegebener unsignierter Entwicklungs-Build.'
        return
    }
    if ($PinnedUpdateCertificateSha256 -notmatch '^[0-9a-fA-F]{64}$') { throw 'Der SHA-256-Pin des Update-Zertifikats wurde für den Produktionsbuild nicht konfiguriert.' }
    $thumbprint = $setupSignature.SignerCertificate.Thumbprint
    foreach ($file in Get-ChildItem -LiteralPath $Payload -File -Recurse -Force | Where-Object Extension -in '.exe','.dll','.ps1') {
        $signature = Get-AuthenticodeSignature -LiteralPath $file.FullName
        if ($signature.Status -ne 'Valid' -or $null -eq $signature.SignerCertificate -or $signature.SignerCertificate.Thumbprint -ne $thumbprint) {
            throw "Payloadsignatur fehlt oder stammt von einem anderen Herausgeber: $($file.Name)"
        }
    }
    $updateCertificate = Join-Path $Payload 'update-public-key.cer'
    $certificateHash = (Get-FileHash -Algorithm SHA256 -LiteralPath $updateCertificate).Hash
    if ($certificateHash -ne $PinnedUpdateCertificateSha256.ToUpperInvariant()) { throw 'Das Update-Zertifikat stimmt nicht mit dem im signierten Setup verankerten SHA-256-Pin überein.' }
}
function Invoke-HealthCheck([string]$Root) {
    try {
        foreach ($file in $RequiredFiles) { if (-not (Test-Path -LiteralPath (Join-Path $Root $file) -PathType Leaf)) { return $false } }
        $null = Test-ManifestAndFiles $Root
        foreach ($name in @('AstroFocusCameraHost.exe','AstroFocusFocuserHost.exe','AstroFocusEngine.exe')) {
            $program = Join-Path $Root $name
            $p = Start-Process -FilePath $program -ArgumentList '--health-check' -Wait -PassThru -WindowStyle Hidden
            if ($p.ExitCode -ne 0) {
                Write-InstallLog "Health-Check $name fehlgeschlagen: Exitcode $($p.ExitCode)."
                return $false
            }
        }
        return $true
    } catch { Write-InstallLog "Health-Check fehlgeschlagen: $($_.Exception.Message)"; return $false }
}
function Save-State([string]$InstalledVersion,[string]$BackupPath) {
    New-Item -ItemType Directory -Force -Path $AdminDataRoot | Out-Null
    [ordered]@{ product=$ProductName; version=$InstalledVersion; installRoot=$InstallRoot; lastBackup=$BackupPath; installedUtc=[DateTime]::UtcNow.ToString('o') } |
        ConvertTo-Json | Set-Content -LiteralPath $StatePath -Encoding UTF8
}
function Register-Uninstall([string]$InstalledVersion) {
    $key = 'HKLM:\Software\Microsoft\Windows\CurrentVersion\Uninstall\AstroFocusStudio'
    New-Item -Force -Path $key | Out-Null
    New-ItemProperty -Path $key -Name DisplayName -Value $ProductName -PropertyType String -Force | Out-Null
    New-ItemProperty -Path $key -Name DisplayVersion -Value $InstalledVersion -PropertyType String -Force | Out-Null
    New-ItemProperty -Path $key -Name Publisher -Value 'Thomas Brotze' -PropertyType String -Force | Out-Null
    New-ItemProperty -Path $key -Name InstallLocation -Value $InstallRoot -PropertyType String -Force | Out-Null
    New-ItemProperty -Path $key -Name DisplayIcon -Value (Join-Path $InstallRoot 'AstroFocusStudio.exe') -PropertyType String -Force | Out-Null
    New-ItemProperty -Path $key -Name UninstallString -Value ('"{0}" -Mode Uninstall' -f (Join-Path $InstallRoot 'AstroFocusSetup.exe')) -PropertyType String -Force | Out-Null
    New-ItemProperty -Path $key -Name QuietUninstallString -Value ('"{0}" -Mode Uninstall -Quiet' -f (Join-Path $InstallRoot 'AstroFocusSetup.exe')) -PropertyType String -Force | Out-Null
    New-ItemProperty -Path $key -Name NoModify -Value 1 -PropertyType DWord -Force | Out-Null
}
function New-Shortcuts {
    $shell = New-Object -ComObject WScript.Shell
    $start = Join-Path $env:ProgramData 'Microsoft\Windows\Start Menu\Programs\AstroFocus Studio.lnk'
    $shortcut = $shell.CreateShortcut($start)
    $shortcut.TargetPath = Join-Path $InstallRoot 'AstroFocusStudio.exe'
    $shortcut.WorkingDirectory = $InstallRoot
    $shortcut.Save()
}
function Trim-Backups {
    if (-not (Test-Path -LiteralPath $RollbackRoot)) { return }
    @(Get-ChildItem -LiteralPath $RollbackRoot -Directory | Sort-Object LastWriteTimeUtc -Descending | Select-Object -Skip 2) | Remove-Item -Recurse -Force
}
function Test-TrustedBackupPath([string]$Backup) {
    if ([string]::IsNullOrWhiteSpace($Backup) -or -not (Test-Path -LiteralPath $Backup -PathType Container)) { throw 'Keine gültige Vorgängerversion für das Rollback vorhanden.' }
    if (-not (Test-IsWithin $Backup $RollbackRoot) -or [IO.Path]::GetFullPath($Backup).TrimEnd('\').Equals([IO.Path]::GetFullPath($RollbackRoot).TrimEnd('\'),[StringComparison]::OrdinalIgnoreCase)) {
        throw 'Rollbackpfad liegt nicht in dem geschützten Rollbackordner.'
    }
    if (Test-IsReparsePoint $Backup) { throw 'Rollbackordner darf kein Reparse Point sein.' }
}
function Restore-Backup([string]$Backup) {
    Test-TrustedBackupPath $Backup
    $manifest = Test-ManifestAndFiles $Backup
    Test-PayloadSignatures $Backup
    if (-not (Invoke-HealthCheck $Backup)) { throw 'Die Vorgängerversion besteht bereits vor dem Rollback den Health-Check nicht.' }
    Stop-AstroFocusProcesses
    $parent = Split-Path $InstallRoot -Parent
    $restoreStage = Join-Path $parent '.AstroFocusStudio.restore'
    $emergency = Join-Path $parent '.AstroFocusStudio.emergency'
    Remove-Item -LiteralPath $restoreStage -Recurse -Force -ErrorAction SilentlyContinue
    Remove-Item -LiteralPath $emergency -Recurse -Force -ErrorAction SilentlyContinue
    New-Item -ItemType Directory -Force -Path $restoreStage | Out-Null
    Copy-Item -Path (Join-Path $Backup '*') -Destination $restoreStage -Recurse -Force
    $null = Test-ManifestAndFiles $restoreStage
    Test-PayloadSignatures $restoreStage
    if (-not (Invoke-HealthCheck $restoreStage)) { throw 'Die vorbereitete Rollbackkopie besteht den Health-Check nicht.' }
    try {
        if (Test-Path -LiteralPath $InstallRoot) { Move-Item -LiteralPath $InstallRoot -Destination $emergency }
        Move-Item -LiteralPath $restoreStage -Destination $InstallRoot
        if (-not (Invoke-HealthCheck $InstallRoot)) { throw 'Die wiederhergestellte Version besteht nach dem Austausch den Health-Check nicht.' }
        Remove-Item -LiteralPath $emergency -Recurse -Force -ErrorAction SilentlyContinue
    } catch {
        Remove-Item -LiteralPath $InstallRoot -Recurse -Force -ErrorAction SilentlyContinue
        if (Test-Path -LiteralPath $emergency) { Move-Item -LiteralPath $emergency -Destination $InstallRoot }
        throw
    } finally { Remove-Item -LiteralPath $restoreStage -Recurse -Force -ErrorAction SilentlyContinue }
    $restoredVersion = [string]$manifest.version
    Register-Uninstall $restoredVersion
    New-Shortcuts
    Save-State $restoredVersion ''
    Write-InstallLog "Rollback auf Version $restoredVersion aus $Backup abgeschlossen."
}
function Install-Product {
    Clear-DevelopmentZoneIdentifiers $Source
    $null = Test-Payload $Source
    Test-PayloadSignatures $Source
    Stop-AstroFocusProcesses
    New-Item -ItemType Directory -Force -Path $RollbackRoot | Out-Null
    $stamp = [DateTime]::UtcNow.ToString('yyyyMMdd-HHmmss')
    $backup = Join-Path $RollbackRoot ("previous-$stamp")
    $backupAvailable = $false
    if (Test-Path -LiteralPath $InstallRoot) {
        try {
            New-Item -ItemType Directory -Force -Path $backup | Out-Null
            Copy-Item -Path (Join-Path $InstallRoot '*') -Destination $backup -Recurse -Force
            $null = Test-ManifestAndFiles $backup
            Test-PayloadSignatures $backup
            if (-not (Invoke-HealthCheck $backup)) { throw 'Health-Check des Backups fehlgeschlagen.' }
            $backupAvailable = $true
        } catch {
            Write-InstallLog "Bestehende Installation konnte nicht als Rollback gesichert werden: $($_.Exception.Message). Reparatur/Update wird ohne Rollback fortgesetzt."
            Remove-Item -LiteralPath $backup -Recurse -Force -ErrorAction SilentlyContinue
            $backup = ''
        }
    }
    $parent = Split-Path $InstallRoot -Parent
    $staging = Join-Path $parent '.AstroFocusStudio.staging'
    $emergency = Join-Path $parent '.AstroFocusStudio.emergency'
    Remove-Item -LiteralPath $staging -Recurse -Force -ErrorAction SilentlyContinue
    Remove-Item -LiteralPath $emergency -Recurse -Force -ErrorAction SilentlyContinue
    New-Item -ItemType Directory -Force -Path $staging | Out-Null
    Copy-Item -Path (Join-Path $Source '*') -Destination $staging -Recurse -Force
    $null = Test-Payload $staging
    Test-PayloadSignatures $staging
    if (-not (Invoke-HealthCheck $staging)) { Remove-Item -LiteralPath $staging -Recurse -Force -ErrorAction SilentlyContinue; throw 'Die vorbereitete neue Version besteht den Health-Check nicht.' }
    try {
        if (Test-Path -LiteralPath $InstallRoot) { Move-Item -LiteralPath $InstallRoot -Destination $emergency }
        Move-Item -LiteralPath $staging -Destination $InstallRoot
        if (-not (Invoke-HealthCheck $InstallRoot)) { throw 'Die neue Version besteht nach dem Austausch den Health-Check nicht.' }
        Register-Uninstall $Version
        New-Shortcuts
        Save-State $Version $backup
        Remove-Item -LiteralPath $emergency -Recurse -Force -ErrorAction SilentlyContinue
        Trim-Backups
        Write-InstallLog "Version $Version erfolgreich installiert. Backup verfügbar: $backupAvailable; Pfad: $backup"
    } catch {
        Write-InstallLog "Installation fehlgeschlagen: $($_.Exception.Message); Wiederherstellung startet."
        Remove-Item -LiteralPath $InstallRoot -Recurse -Force -ErrorAction SilentlyContinue
        if (Test-Path -LiteralPath $emergency) {
            Move-Item -LiteralPath $emergency -Destination $InstallRoot
            Write-InstallLog 'Vorheriger Installationsordner wurde aus dem Notfall-Swap wiederhergestellt.'
        } elseif ($backupAvailable) { Restore-Backup $backup }
        throw
    } finally {
        Remove-Item -LiteralPath $staging -Recurse -Force -ErrorAction SilentlyContinue
        Remove-Item -LiteralPath $emergency -Recurse -Force -ErrorAction SilentlyContinue
    }
}
function Repair-Product {
    if (Test-Path -LiteralPath $Source -PathType Container) { Install-Product; return }
    if (Invoke-HealthCheck $InstallRoot) { Write-InstallLog 'Reparaturprüfung: bestehende Installation ist vollständig und gesund.'; return }
    if (Test-Path -LiteralPath $StatePath -PathType Leaf) {
        $state = Get-Content -LiteralPath $StatePath -Raw -Encoding UTF8 | ConvertFrom-Json
        if ($state.product -eq $ProductName -and [string]$state.installRoot -eq $InstallRoot -and -not [string]::IsNullOrWhiteSpace([string]$state.lastBackup)) {
            Restore-Backup ([string]$state.lastBackup)
            return
        }
    }
    throw 'Die Installation ist beschädigt und es wurde weder ein vollständiges Reparatur-Payload noch ein gültiges Rollback gefunden.'
}
function Read-RollbackState {
    if (-not (Test-Path -LiteralPath $StatePath -PathType Leaf)) { throw 'Installationsstatus für das Rollback fehlt.' }
    if (Test-IsReparsePoint $StatePath) { throw 'Installationsstatus darf kein Reparse Point sein.' }
    $state = Get-Content -LiteralPath $StatePath -Raw -Encoding UTF8 | ConvertFrom-Json
    if ($state.product -ne $ProductName -or [string]$state.installRoot -ne $InstallRoot) { throw 'Installationsstatus gehört nicht zu dieser Installation.' }
    return $state
}
function Schedule-TempCleanup {
    if (-not $InternalRelocated) { return }
    $tempRoot = $ScriptDirectory
    $cmd = Join-Path $env:SystemRoot 'System32\cmd.exe'
    $escaped = $tempRoot.Replace('"','""')
    $cleanupCommand = ('ping 127.0.0.1 -n 3 >nul & rmdir /s /q "{0}"' -f $escaped)
    Start-Process -FilePath $cmd -WindowStyle Hidden -ArgumentList @('/d','/c',$cleanupCommand) | Out-Null
}

try {
    Start-RelocatedDestructiveMode
    Wait-ForPreviousInstance
    Request-Elevation
    Enter-MaintenanceMutex
    Enter-InstallerMutex
    if ($AllowUnsignedDevelopment -and -not (Test-DevelopmentModeAllowed)) { throw 'Der unsignierte Entwicklungsmodus ist ohne lokale Bundle-Markierung gesperrt.' }
    switch ($Mode) {
        'Install' { Install-Product }
        'Repair' { Repair-Product }
        'Health' { if (-not (Invoke-HealthCheck $InstallRoot)) { exit 20 } }
        'Rollback' { $state = Read-RollbackState; Restore-Backup ([string]$state.lastBackup) }
        'Uninstall' {
            Stop-AstroFocusProcesses
            if (Test-Path -LiteralPath $InstallRoot) { Remove-Item -LiteralPath $InstallRoot -Recurse -Force }
            Remove-Item -LiteralPath 'HKLM:\Software\Microsoft\Windows\CurrentVersion\Uninstall\AstroFocusStudio' -Recurse -Force -ErrorAction SilentlyContinue
            Remove-Item -LiteralPath (Join-Path $env:ProgramData 'Microsoft\Windows\Start Menu\Programs\AstroFocus Studio.lnk') -Force -ErrorAction SilentlyContinue
            Write-InstallLog 'Programmdateien deinstalliert; Benutzerdaten, Profile und administrative Diagnoseprotokolle wurden beibehalten.'
        }
    }
    if (-not $Quiet) { Show-InstallerMessage (Get-ModeSuccessMessage) }
    Schedule-TempCleanup
    exit 0
} catch {
    try { Write-InstallLog "FEHLER: $($_.Exception.Message)" } catch {}
    if (-not $Quiet) {
        Show-InstallerMessage ("$($_.Exception.Message)`n`nDiagnoseprotokoll: $LogPath") -ErrorIcon
    }
    Schedule-TempCleanup
    exit 1
}
