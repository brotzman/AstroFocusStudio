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

$tests = @(Get-ChildItem -LiteralPath $testsDirectory -Filter '*.py' -File | Sort-Object Name)
if ($tests.Count -eq 0) {
    throw 'Keine Python-Regressionstests gefunden.'
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
