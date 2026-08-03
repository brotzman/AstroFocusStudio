[CmdletBinding()]
param(
    [ValidateSet('Check','Apply','Rollback','Health')]
    [string]$Mode = 'Check',
    [string]$Manifest,
    [ValidateSet('stable','preview')]
    [string]$Channel = 'stable',
    [switch]$Quiet,
    [switch]$AllowUnsignedDevelopment,
    [switch]$InternalRelocated,
    [int]$WaitForProcessId = 0
)
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'
$Product = 'AstroFocus Studio'
$InstallRoot = Join-Path $env:ProgramFiles $Product
$BundledVersion = [version]'0.0.0'
foreach ($candidate in @((Join-Path $PSScriptRoot 'release-manifest.json'), (Join-Path $InstallRoot 'release-manifest.json'), (Join-Path $PSScriptRoot '..\VERSION'))) {
    if (-not (Test-Path -LiteralPath $candidate -PathType Leaf)) { continue }
    try {
        $text = if ([IO.Path]::GetFileName($candidate) -eq 'VERSION') { (Get-Content -LiteralPath $candidate -Raw -Encoding UTF8).Trim() } else { [string]((Get-Content -LiteralPath $candidate -Raw -Encoding UTF8 | ConvertFrom-Json).version) }
        if ($text -match '^(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)$') { $BundledVersion = [version]$text; break }
    } catch { }
}
if ($BundledVersion -eq [version]'0.0.0') { throw 'Die gebündelte AstroFocus-Version konnte nicht bestimmt werden.' }
$DataRoot = Join-Path $env:LOCALAPPDATA 'AstroFocusStudio'
$UpdateRoot = Join-Path $DataRoot 'Updates'
$StagingRoot = Join-Path $UpdateRoot 'staging'
$CacheRoot = Join-Path $UpdateRoot 'packages'
$LogRoot = Join-Path $DataRoot 'Logs'
$LogPath = Join-Path $LogRoot 'Updater.log'
$PublicKeyPath = Join-Path $PSScriptRoot 'update-public-key.cer'
$DevMarkerName = 'UNSIGNED_DEVELOPMENT_BUILD.txt'
$MaximumManifestBytes = 1MB
$MaximumPackageBytes = 512MB
$MaximumArchiveFiles = 256
$MaximumArchiveBytes = 1GB

function Enter-MaintenanceMutex {
    try {
        $script:MaintenanceMutex = [System.Threading.Mutex]::new($false,'Global\AstroFocusStudio.Maintenance')
        if (-not $script:MaintenanceMutex.WaitOne(0)) { throw 'Eine AstroFocus-Installation oder ein Update läuft bereits.' }
    } catch [System.Threading.AbandonedMutexException] {
        Write-UpdateLog 'Verwaiste gemeinsame Wartungssperre übernommen.'
    } catch [System.UnauthorizedAccessException] {
        throw 'Eine AstroFocus-Installation oder ein Update läuft bereits oder die gemeinsame Wartungssperre ist nicht zugänglich.'
    }
}
function Enter-UpdaterMutex {
    $script:UpdaterMutex = [System.Threading.Mutex]::new($false,'Local\AstroFocusStudio.Updater')
    try {
        if (-not $script:UpdaterMutex.WaitOne(0)) { throw 'Ein anderer AstroFocus-Updater läuft bereits.' }
    } catch [System.Threading.AbandonedMutexException] {
        Write-UpdateLog 'Verwaiste Updater-Sperre übernommen.'
    }
}
function Write-UpdateLog([string]$Message) {
    New-Item -ItemType Directory -Force -Path $LogRoot | Out-Null
    Add-Content -LiteralPath $LogPath -Encoding UTF8 -Value ("{0:o} | {1}" -f [DateTime]::UtcNow,$Message)
}
function Test-IsWithin([string]$Child,[string]$Parent) {
    $childFull = [IO.Path]::GetFullPath($Child).TrimEnd('\')
    $parentFull = [IO.Path]::GetFullPath($Parent).TrimEnd('\')
    return $childFull.Equals($parentFull,[StringComparison]::OrdinalIgnoreCase) -or $childFull.StartsWith($parentFull + '\',[StringComparison]::OrdinalIgnoreCase)
}
function Test-SafeWindowsRelativePath([string]$Relative,[string]$Context) {
    if ([string]::IsNullOrWhiteSpace($Relative) -or [IO.Path]::IsPathRooted($Relative) -or $Relative.Contains(':')) { throw "Ungültiger $Context-Pfad: $Relative" }
    $normal = $Relative.Replace('/','\').TrimEnd('\')
    if ([string]::IsNullOrWhiteSpace($normal)) { throw "Leerer $Context-Pfad." }
    foreach ($segment in $normal.Split('\')) {
        if ([string]::IsNullOrWhiteSpace($segment) -or $segment -eq '.' -or $segment -eq '..' -or $segment.EndsWith('.') -or $segment.EndsWith(' ')) { throw "Unsicherer $Context-Pfad: $Relative" }
        if ($segment -match '^(?i:CON|PRN|AUX|NUL|COM[1-9]|LPT[1-9])(?:\..*)?$') { throw "Reservierter Windows-Name im $Context-Pfad: $Relative" }
    }
    return $normal
}
function Get-InstalledVersion {
    $manifestPath = Join-Path $InstallRoot 'release-manifest.json'
    if (Test-Path -LiteralPath $manifestPath -PathType Leaf) {
        try {
            $manifest = Get-Content -LiteralPath $manifestPath -Raw -Encoding UTF8 | ConvertFrom-Json
            if ($manifest.product -eq $Product) { return [version][string]$manifest.version }
        } catch { Write-UpdateLog "Installierte Version konnte nicht aus dem Release-Manifest gelesen werden: $($_.Exception.Message)" }
    }
    Write-UpdateLog 'Kein gültiges Installationsmanifest vorhanden; installierte Version wird als 0.0.0 behandelt.'
    return [version]'0.0.0'
}
function Test-DevelopmentModeAllowed([string]$PayloadRoot = '') {
    if (-not $AllowUnsignedDevelopment) { return $false }
    $bundleMarker = Join-Path $PSScriptRoot $DevMarkerName
    if (-not (Test-Path -LiteralPath $bundleMarker -PathType Leaf)) { return $false }
    if (-not [string]::IsNullOrWhiteSpace($PayloadRoot)) {
        $payloadMarker = Join-Path $PayloadRoot $DevMarkerName
        if (-not (Test-Path -LiteralPath $payloadMarker -PathType Leaf)) { return $false }
    }
    return $true
}
function Start-RelocatedMode {
    if ($InternalRelocated -or $Mode -notin @('Apply','Rollback')) { return }
    if (-not (Test-IsWithin $PSScriptRoot $InstallRoot)) { return }
    $tempRoot = Join-Path $env:TEMP ("AstroFocusUpdater-{0}" -f [Guid]::NewGuid().ToString('N'))
    New-Item -ItemType Directory -Force -Path $tempRoot | Out-Null
    foreach ($name in @('AstroFocusUpdater.exe','AstroFocusUpdater.ps1','update-public-key.cer',$DevMarkerName)) {
        $from = Join-Path $PSScriptRoot $name
        if (Test-Path -LiteralPath $from -PathType Leaf) { Copy-Item -LiteralPath $from -Destination (Join-Path $tempRoot $name) -Force }
    }
    $launcher = Join-Path $tempRoot 'AstroFocusUpdater.exe'
    if (-not (Test-Path -LiteralPath $launcher -PathType Leaf)) { throw 'Der Updater konnte nicht sicher in den Temp-Ordner kopiert werden.' }
    $arguments = @('-Mode',$Mode,'-Channel',$Channel,'-Quiet','-InternalRelocated','-WaitForProcessId',$PID)
    if (-not [string]::IsNullOrWhiteSpace($Manifest)) { $arguments += @('-Manifest',('"{0}"' -f $Manifest)) }
    if ($AllowUnsignedDevelopment) { $arguments += '-AllowUnsignedDevelopment' }
    Start-Process -FilePath $launcher -ArgumentList $arguments | Out-Null
    exit 0
}
function Wait-ForPreviousInstance {
    if ($WaitForProcessId -le 0) { return }
    try { Wait-Process -Id $WaitForProcessId -Timeout 30 -ErrorAction SilentlyContinue } catch {}
    Start-Sleep -Milliseconds 800
}
function Schedule-TempCleanup {
    if (-not $InternalRelocated) { return }
    $tempRoot = $PSScriptRoot
    $cmd = Join-Path $env:SystemRoot 'System32\cmd.exe'
    $escaped = $tempRoot.Replace('"','""')
    $cleanup = ('ping 127.0.0.1 -n 3 >nul & rmdir /s /q "{0}"' -f $escaped)
    Start-Process -FilePath $cmd -WindowStyle Hidden -ArgumentList @('/d','/c',$cleanup) | Out-Null
}
function Get-WebResponse([Uri]$Uri,[string]$OutFile = '') {
    if ($Uri.Scheme -ne 'https') { throw 'Produktionsupdates müssen über HTTPS geladen werden.' }
    if ([string]::IsNullOrWhiteSpace($OutFile)) {
        $response = Invoke-WebRequest -UseBasicParsing -Uri $Uri -TimeoutSec 30 -MaximumRedirection 5
    } else {
        $response = Invoke-WebRequest -UseBasicParsing -Uri $Uri -OutFile $OutFile -TimeoutSec 600 -MaximumRedirection 5 -PassThru
    }
    $finalUri = $null
    try { $finalUri = [Uri]$response.BaseResponse.ResponseUri } catch {}
    if ($null -ne $finalUri -and $finalUri.Scheme -ne 'https') { throw 'Eine HTTP-Weiterleitung hat die sichere HTTPS-Verbindung verlassen.' }
    return $response
}
function Get-ManifestText([string]$Location) {
    if ([string]::IsNullOrWhiteSpace($Location)) { throw 'Keine Manifestquelle angegeben.' }
    if ([Uri]::IsWellFormedUriString($Location,[UriKind]::Absolute)) {
        $uri = [Uri]$Location
        if ($uri.Scheme -eq 'file' -and (Test-DevelopmentModeAllowed)) {
            $path = $uri.LocalPath
            if ((Get-Item -LiteralPath $path).Length -gt $MaximumManifestBytes) { throw 'Update-Manifest ist zu groß.' }
            return Get-Content -LiteralPath $path -Raw -Encoding UTF8
        }
        $response = Get-WebResponse $uri
        $content = [string]$response.Content
        if ([Text.Encoding]::UTF8.GetByteCount($content) -gt $MaximumManifestBytes) { throw 'Update-Manifest ist zu groß.' }
        return $content
    }
    if (-not (Test-DevelopmentModeAllowed)) { throw 'Lokale Update-Manifeste sind nur im ausdrücklich markierten Entwicklungsmodus erlaubt.' }
    if ((Get-Item -LiteralPath $Location).Length -gt $MaximumManifestBytes) { throw 'Update-Manifest ist zu groß.' }
    return Get-Content -LiteralPath $Location -Raw -Encoding UTF8
}
function Get-CanonicalManifestPayload($ManifestObject) {
    return @(
        [string]$ManifestObject.product,
        [string]$ManifestObject.channel,
        [string]$ManifestObject.version,
        [string]$ManifestObject.packageUrl,
        ([string]$ManifestObject.sha256).ToLowerInvariant(),
        [string]$ManifestObject.publisher,
        [string]$ManifestObject.minimumSupportedVersion
    ) -join "`n"
}
function Test-ManifestSignature($ManifestObject) {
    if ((Test-DevelopmentModeAllowed) -and [string]::IsNullOrWhiteSpace([string]$ManifestObject.signature)) { return $true }
    if (-not (Test-Path -LiteralPath $PublicKeyPath -PathType Leaf)) { throw 'Öffentliches Update-Zertifikat fehlt.' }
    $certificate = [Security.Cryptography.X509Certificates.X509Certificate2]::new($PublicKeyPath)
    $rsa = [Security.Cryptography.X509Certificates.RSACertificateExtensions]::GetRSAPublicKey($certificate)
    if ($null -eq $rsa) { $certificate.Dispose(); throw 'Update-Zertifikat enthält keinen RSA-Schlüssel.' }
    try {
        $data = [Text.Encoding]::UTF8.GetBytes((Get-CanonicalManifestPayload $ManifestObject))
        $signature = [Convert]::FromBase64String([string]$ManifestObject.signature)
        return $rsa.VerifyData($data,$signature,[Security.Cryptography.HashAlgorithmName]::SHA256,[Security.Cryptography.RSASignaturePadding]::Pkcs1)
    } finally { $rsa.Dispose(); $certificate.Dispose() }
}
function Read-And-ValidateManifest([string]$Location,[version]$CurrentVersion) {
    $manifestObject = (Get-ManifestText $Location) | ConvertFrom-Json
    foreach ($name in @('product','channel','version','minimumSupportedVersion','packageUrl','sha256','publisher','signature')) {
        if (-not $manifestObject.PSObject.Properties.Name.Contains($name)) { throw "Manifestfeld fehlt: $name" }
    }
    foreach ($name in @('product','channel','version','minimumSupportedVersion','packageUrl','sha256','publisher')) {
        if ([string]::IsNullOrWhiteSpace([string]$manifestObject.$name)) { throw "Manifestfeld ist leer: $name" }
    }
    if ($manifestObject.product -ne $Product) { throw 'Manifest gehört zu einem anderen Produkt.' }
    if ($manifestObject.channel -ne $Channel) { throw "Manifestkanal $($manifestObject.channel) stimmt nicht mit $Channel überein." }
    $targetVersion = [version][string]$manifestObject.version
    $minimumVersion = [version][string]$manifestObject.minimumSupportedVersion
    if ($minimumVersion -gt $CurrentVersion) { throw 'Die installierte Version ist für dieses direkte Update zu alt.' }
    if ([string]$manifestObject.sha256 -notmatch '^[0-9a-fA-F]{64}$') { throw 'Ungültiger SHA-256-Wert im Update-Manifest.' }
    $packageUri = $null
    if ([Uri]::IsWellFormedUriString([string]$manifestObject.packageUrl,[UriKind]::Absolute)) { $packageUri = [Uri][string]$manifestObject.packageUrl }
    if ($null -ne $packageUri -and $packageUri.Scheme -ne 'https' -and -not ((Test-DevelopmentModeAllowed) -and $packageUri.Scheme -eq 'file')) { throw 'Updatepakete müssen über HTTPS geladen werden.' }
    if (-not (Test-ManifestSignature $manifestObject)) { throw 'Kryptografische Signatur des Update-Manifests ist ungültig.' }
    return $manifestObject
}
function Copy-Or-Download([string]$Source,[string]$Destination) {
    $partial = $Destination + '.partial'
    Remove-Item -LiteralPath $partial -Force -ErrorAction SilentlyContinue
    try {
        if ([Uri]::IsWellFormedUriString($Source,[UriKind]::Absolute)) {
            $uri = [Uri]$Source
            if ($uri.Scheme -eq 'file' -and (Test-DevelopmentModeAllowed)) { Copy-Item -LiteralPath $uri.LocalPath -Destination $partial -Force }
            else { $null = Get-WebResponse $uri $partial }
        } else {
            if (-not (Test-DevelopmentModeAllowed)) { throw 'Lokale Updatepakete sind nur im ausdrücklich markierten Entwicklungsmodus erlaubt.' }
            Copy-Item -LiteralPath $Source -Destination $partial -Force
        }
        $length = (Get-Item -LiteralPath $partial).Length
        if ($length -le 0 -or $length -gt $MaximumPackageBytes) { throw 'Updatepaket ist leer oder überschreitet die zulässige Größe.' }
        Move-Item -LiteralPath $partial -Destination $Destination -Force
    } catch { Remove-Item -LiteralPath $partial -Force -ErrorAction SilentlyContinue; throw }
}
function Expand-SafeArchive([string]$Archive,[string]$Destination) {
    Add-Type -AssemblyName System.IO.Compression.FileSystem
    Remove-Item -LiteralPath $Destination -Recurse -Force -ErrorAction SilentlyContinue
    New-Item -ItemType Directory -Force -Path $Destination | Out-Null
    $root = [IO.Path]::GetFullPath($Destination).TrimEnd('\')
    $seen = [Collections.Generic.HashSet[string]]::new([StringComparer]::OrdinalIgnoreCase)
    $archiveObject = [IO.Compression.ZipFile]::OpenRead($Archive)
    try {
        if ($archiveObject.Entries.Count -gt $MaximumArchiveFiles) { throw 'Updatearchiv enthält zu viele Einträge.' }
        [long]$total = 0
        foreach ($entry in $archiveObject.Entries) {
            $relative = Test-SafeWindowsRelativePath ([string]$entry.FullName) 'Archiv'
            $key = $relative.TrimEnd('\')
            if (-not $seen.Add($key)) { throw "Doppelter oder kollidierender Archivpfad: $relative" }
            $total += [long]$entry.Length
            if ($total -gt $MaximumArchiveBytes) { throw 'Entpackte Archivgröße überschreitet die Sicherheitsgrenze.' }
            $target = [IO.Path]::GetFullPath((Join-Path $root $relative))
            if (-not $target.StartsWith($root + '\',[StringComparison]::OrdinalIgnoreCase)) { throw "Archivpfad verlässt den Zielordner: $relative" }
            if ([string]::IsNullOrEmpty($entry.Name)) { New-Item -ItemType Directory -Force -Path $target | Out-Null; continue }
            New-Item -ItemType Directory -Force -Path (Split-Path $target -Parent) | Out-Null
            $input = $entry.Open()
            try {
                $output = [IO.File]::Open($target,[IO.FileMode]::CreateNew,[IO.FileAccess]::Write,[IO.FileShare]::None)
                try { $input.CopyTo($output) } finally { $output.Dispose() }
            } finally { $input.Dispose() }
        }
    } finally { $archiveObject.Dispose() }
}
function Find-BundleRoot([string]$Root) {
    $bundleRoots = @(
        Get-ChildItem -LiteralPath $Root -Filter AstroFocusSetup.exe -File -Recurse | ForEach-Object {
            $candidate = $_.Directory.FullName
            $scriptPath = Join-Path $candidate 'AstroFocusSetup.ps1'
            $payloadPath = Join-Path $candidate 'payload'
            if ((Test-Path -LiteralPath $scriptPath -PathType Leaf) -and
                (Test-Path -LiteralPath $payloadPath -PathType Container)) {
                $candidate
            }
        } | Sort-Object -Unique
    )
    if ($bundleRoots.Count -ne 1) { throw 'Updatepaket muss genau ein vollständiges Setup-Bundle enthalten.' }
    $bundleRoot = [string]$bundleRoots[0]
    if (-not (Test-IsWithin $bundleRoot $Root)) { throw 'Setup-Bundle liegt außerhalb des Staging-Ordners.' }
    return $bundleRoot
}
function Read-BundleReleaseManifest([string]$BundleRoot,[version]$ExpectedVersion) {
    $payload = Join-Path $BundleRoot 'payload'
    $manifestPath = Join-Path $payload 'release-manifest.json'
    if (-not (Test-Path -LiteralPath $manifestPath -PathType Leaf)) { throw 'Release-Manifest im Update-Payload fehlt.' }
    $release = Get-Content -LiteralPath $manifestPath -Raw -Encoding UTF8 | ConvertFrom-Json
    if ($release.product -ne $Product -or [version][string]$release.version -ne $ExpectedVersion) { throw 'Release-Manifest des Payloads stimmt nicht mit dem signierten Update-Manifest überein.' }
    if ($release.architecture -ne 'windows-x64') { throw 'Update-Payload hat eine unerwartete Architektur.' }
    if ($AllowUnsignedDevelopment -and -not (Test-DevelopmentModeAllowed $payload)) { throw 'Unsicherer Entwicklungsmodus: Bundle- und Payload-Markierung müssen gemeinsam vorhanden sein.' }
    return $release
}
function Test-PackageSignature([string]$SetupExe,[string]$ExpectedPublisher) {
    $signature = Get-AuthenticodeSignature -LiteralPath $SetupExe
    if ((Test-DevelopmentModeAllowed) -and $signature.Status -eq 'NotSigned') { return }
    if ($signature.Status -ne 'Valid') { throw "Authenticode-Prüfung fehlgeschlagen: $($signature.Status)" }
    if (-not [string]::IsNullOrWhiteSpace($ExpectedPublisher) -and $signature.SignerCertificate.Subject -notlike "*$ExpectedPublisher*") { throw 'Der Herausgeber des Setups stimmt nicht mit dem Manifest überein.' }
}
function Invoke-Setup([string]$BundleRoot,[string]$SetupMode) {
    $setup = Join-Path $BundleRoot 'AstroFocusSetup.exe'
    $payload = Join-Path $BundleRoot 'payload'
    $arguments = @('-Mode',$SetupMode,'-Quiet')
    if ($SetupMode -in @('Install','Repair')) { $arguments += @('-Source',('"{0}"' -f $payload)) }
    if ($AllowUnsignedDevelopment) { $arguments += '-AllowUnsignedDevelopment' }
    $process = Start-Process -FilePath $setup -ArgumentList $arguments -Wait -PassThru
    if ($process.ExitCode -ne 0) { throw "Setup meldete Exitcode $($process.ExitCode)." }
}
function Test-InstalledHealth([version]$ExpectedVersion) {
    $setup = Join-Path $InstallRoot 'AstroFocusSetup.exe'
    if (-not (Test-Path -LiteralPath $setup -PathType Leaf)) { return $false }
    $process = Start-Process -FilePath $setup -ArgumentList @('-Mode','Health','-Quiet') -Wait -PassThru
    if ($process.ExitCode -ne 0) { return $false }
    try { return (Get-InstalledVersion) -eq $ExpectedVersion } catch { return $false }
}
function Get-HealthyInstalledVersion {
    try {
        $manifestPath = Join-Path $InstallRoot 'release-manifest.json'
        if (-not (Test-Path -LiteralPath $manifestPath -PathType Leaf)) { return $null }
        $manifest = Get-Content -LiteralPath $manifestPath -Raw -Encoding UTF8 | ConvertFrom-Json
        if ($manifest.product -ne $Product -or [string]::IsNullOrWhiteSpace([string]$manifest.version)) { return $null }
        $version = [version][string]$manifest.version
        if (-not (Test-InstalledHealth $version)) { return $null }
        return $version
    } catch { Write-UpdateLog "Installierter Zustand konnte nicht sicher validiert werden: $($_.Exception.Message)"; return $null }
}
function Trim-PackageCache {
    if (-not (Test-Path -LiteralPath $CacheRoot)) { return }
    @(Get-ChildItem -LiteralPath $CacheRoot -File | Sort-Object LastWriteTimeUtc -Descending | Select-Object -Skip 2) | Remove-Item -Force
}
function Apply-Update($ManifestObject) {
    $targetVersion = [version][string]$ManifestObject.version
    New-Item -ItemType Directory -Force -Path $StagingRoot,$CacheRoot | Out-Null
    Remove-Item -LiteralPath $StagingRoot -Recurse -Force -ErrorAction SilentlyContinue
    New-Item -ItemType Directory -Force -Path $StagingRoot | Out-Null
    $package = Join-Path $CacheRoot ("AstroFocusStudio-{0}-Setup.zip" -f $targetVersion)
    Copy-Or-Download ([string]$ManifestObject.packageUrl) $package
    $actual = (Get-FileHash -Algorithm SHA256 -LiteralPath $package).Hash.ToLowerInvariant()
    if ($actual -ne ([string]$ManifestObject.sha256).ToLowerInvariant()) { Remove-Item -LiteralPath $package -Force; throw 'SHA-256 des Updatepakets stimmt nicht.' }
    Expand-SafeArchive $package $StagingRoot
    $bundleRoot = Find-BundleRoot $StagingRoot
    $payload = Join-Path $bundleRoot 'payload'
    $null = Read-BundleReleaseManifest $bundleRoot $targetVersion
    Test-PackageSignature (Join-Path $bundleRoot 'AstroFocusSetup.exe') ([string]$ManifestObject.publisher)
    Write-UpdateLog "Update $targetVersion verifiziert; Installation beginnt."
    try {
        Invoke-Setup $bundleRoot 'Install'
        if (-not (Test-InstalledHealth $targetVersion)) { throw 'Installierte Zielversion besteht den Health- oder Versionscheck nicht.' }
        Write-UpdateLog "Update $targetVersion erfolgreich und Health-Check bestanden."
        Trim-PackageCache
    } catch {
        $failure = $_.Exception.Message
        Write-UpdateLog "Update fehlgeschlagen: $failure"
        $healthyVersion = Get-HealthyInstalledVersion
        if ($null -ne $healthyVersion) {
            Write-UpdateLog 'Die Installation ist nach dem Fehler bereits gesund; das Setup hat den Notfall-Swap selbst zurückgenommen.'
            Write-UpdateLog "Validierte installierte Version: $healthyVersion"
        } else {
            Write-UpdateLog 'Installierte Version ist nicht gesund; explizites Rollback wird angefordert.'
            $installedSetup = Join-Path $InstallRoot 'AstroFocusSetup.exe'
            if (Test-Path -LiteralPath $installedSetup -PathType Leaf) {
                $rollback = Start-Process -FilePath $installedSetup -ArgumentList @('-Mode','Rollback','-Quiet') -Wait -PassThru
                if ($rollback.ExitCode -ne 0) { Write-UpdateLog "Rollback meldete Exitcode $($rollback.ExitCode)." }
                elseif ($null -eq (Get-HealthyInstalledVersion)) { Write-UpdateLog 'Rollback wurde ausgeführt, aber der nachfolgende Health- und Manifestcheck ist fehlgeschlagen.' }
                else { Write-UpdateLog 'Rollback und Health-Check waren erfolgreich.' }
            } else { Write-UpdateLog 'Explizites Rollback nicht möglich: installiertes Setupwerkzeug fehlt.' }
        }
        throw
    } finally { Remove-Item -LiteralPath $StagingRoot -Recurse -Force -ErrorAction SilentlyContinue }
}

Start-RelocatedMode
Wait-ForPreviousInstance
try {
    Enter-MaintenanceMutex
    Enter-UpdaterMutex
    if ($AllowUnsignedDevelopment -and -not (Test-DevelopmentModeAllowed)) { throw 'Der unsignierte Entwicklungsmodus ist ohne lokale Bundle-Markierung gesperrt.' }
    $currentVersion = Get-InstalledVersion
    if ($currentVersion -eq [version]'0.0.0' -and (Test-Path -LiteralPath $InstallRoot -PathType Container) -and $Mode -in @('Check','Apply')) {
        throw 'Die vorhandene Installation besitzt kein gültiges Release-Manifest. Führe zuerst Reparatur oder Rollback aus.'
    }
    switch ($Mode) {
        'Check' {
            $manifestObject = Read-And-ValidateManifest $Manifest $currentVersion
            [pscustomobject]@{
                UpdateAvailable = ([version][string]$manifestObject.version -gt $currentVersion)
                CurrentVersion = $currentVersion.ToString()
                Version = [string]$manifestObject.version
                Channel = [string]$manifestObject.channel
            } | ConvertTo-Json
        }
        'Apply' {
            $manifestObject = Read-And-ValidateManifest $Manifest $currentVersion
            if ([version][string]$manifestObject.version -le $currentVersion) { throw 'Das Manifest enthält keine neuere Version.' }
            Apply-Update $manifestObject
        }
        'Rollback' {
            $setup = Join-Path $InstallRoot 'AstroFocusSetup.exe'
            if (-not (Test-Path -LiteralPath $setup -PathType Leaf)) { throw 'Installiertes Setupwerkzeug fehlt.' }
            $process = Start-Process -FilePath $setup -ArgumentList @('-Mode','Rollback','-Quiet') -Wait -PassThru
            if ($process.ExitCode -ne 0) { throw "Rollback-Exitcode $($process.ExitCode)" }
        }
        'Health' {
            if ($null -eq (Get-HealthyInstalledVersion)) { exit 20 }
        }
    }
    Schedule-TempCleanup
    exit 0
} catch {
    Write-UpdateLog "FEHLER: $($_.Exception.Message)"
    if (-not $Quiet) { Write-Error $_ }
    Schedule-TempCleanup
    exit 1
}
