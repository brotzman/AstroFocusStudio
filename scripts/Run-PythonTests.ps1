[CmdletBinding()]
param(
    [string]$RepositoryRoot = (Split-Path -Parent $PSScriptRoot),
    [string]$LogPath = ''
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'
$env:PYTHONDONTWRITEBYTECODE = '1'

$RepositoryRoot = [IO.Path]::GetFullPath($RepositoryRoot)
if ([string]::IsNullOrWhiteSpace($LogPath)) {
    $LogPath = Join-Path $RepositoryRoot 'artifacts\test-logs\python-tests.log'
}
$LogPath = [IO.Path]::GetFullPath($LogPath)
$logDirectory = Split-Path -Parent $LogPath
New-Item -ItemType Directory -Force -Path $logDirectory | Out-Null
Set-Content -LiteralPath $LogPath -Value '' -Encoding utf8

$python = Get-Command python.exe -ErrorAction SilentlyContinue
if ($null -eq $python) {
    $python = Get-Command python -ErrorAction SilentlyContinue
}
if ($null -eq $python) {
    throw 'Python wurde nicht gefunden.'
}

$testsDirectory = Join-Path $RepositoryRoot 'tests'
if (-not (Test-Path -LiteralPath $testsDirectory -PathType Container)) {
    throw "Testverzeichnis fehlt: $testsDirectory"
}

$cleanupScript = Join-Path $RepositoryRoot 'scripts\remove_legacy_version_files.py'
if (-not (Test-Path -LiteralPath $cleanupScript -PathType Leaf)) {
    throw "Versionsbereinigung fehlt: $cleanupScript"
}
$cleanupLog = Join-Path $logDirectory 'legacy-version-cleanup.log'
$cleanup = Start-Process `
    -FilePath $python.Source `
    -ArgumentList @('-B', '-X', 'utf8', $cleanupScript, '--root', $RepositoryRoot, '--log', $cleanupLog) `
    -WorkingDirectory $RepositoryRoot `
    -NoNewWindow `
    -Wait `
    -PassThru
if ($cleanup.ExitCode -ne 0) {
    throw "Bereinigung alter Versionsdateien fehlgeschlagen (Exitcode $($cleanup.ExitCode)): $cleanupLog"
}

$currentSuffix = '_390.py'
$versionTestName = 'version_consistency_validation_390.py'
$allCurrentTests = @(Get-ChildItem -LiteralPath $testsDirectory -Filter "*$currentSuffix" -File | Sort-Object Name)
$versionTest = @($allCurrentTests | Where-Object Name -EQ $versionTestName)
$remainingTests = @($allCurrentTests | Where-Object Name -NE $versionTestName)
$tests = @($versionTest + $remainingTests)
if ($versionTest.Count -ne 1) {
    throw "Versionskonsistenztest fehlt oder ist doppelt vorhanden: $versionTestName"
}
if ($tests.Count -eq 0) {
    throw 'Keine Python-Regressionstests der Version 3.9.0 gefunden.'
}

function Write-TestOutput([string]$Text) {
    if ([string]::IsNullOrEmpty($Text)) {
        return
    }
    $Text.TrimEnd("`r", "`n") | Tee-Object -FilePath $LogPath -Append | Write-Host
}

foreach ($test in $tests) {
    $header = "==> $($test.Name)"
    $header | Tee-Object -FilePath $LogPath -Append | Write-Host

    $stdoutPath = Join-Path $env:TEMP ("afs-python-stdout-{0}.txt" -f [Guid]::NewGuid().ToString('N'))
    $stderrPath = Join-Path $env:TEMP ("afs-python-stderr-{0}.txt" -f [Guid]::NewGuid().ToString('N'))
    try {
        $process = Start-Process `
            -FilePath $python.Source `
            -ArgumentList @('-X', 'utf8', $test.FullName) `
            -WorkingDirectory $RepositoryRoot `
            -NoNewWindow `
            -Wait `
            -PassThru `
            -RedirectStandardOutput $stdoutPath `
            -RedirectStandardError $stderrPath

        $stdout = if (Test-Path -LiteralPath $stdoutPath) {
            Get-Content -LiteralPath $stdoutPath -Raw -Encoding utf8
        } else { '' }
        $stderr = if (Test-Path -LiteralPath $stderrPath) {
            Get-Content -LiteralPath $stderrPath -Raw -Encoding utf8
        } else { '' }

        Write-TestOutput $stdout
        if (-not [string]::IsNullOrWhiteSpace($stderr)) {
            Write-TestOutput $stderr
        }

        if ($process.ExitCode -ne 0) {
            throw "Test fehlgeschlagen: $($test.Name) (Exitcode $($process.ExitCode)). Vollständiges Protokoll: $LogPath"
        }
    } finally {
        Remove-Item -LiteralPath $stdoutPath, $stderrPath -Force -ErrorAction SilentlyContinue
    }
}

"Alle $($tests.Count) Python-Testprogramme wurden bestanden." |
    Tee-Object -FilePath $LogPath -Append | Write-Host
