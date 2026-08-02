[CmdletBinding()]
param(
    [string]$RepositoryRoot = (Split-Path -Parent $PSScriptRoot)
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'
$env:PYTHONDONTWRITEBYTECODE = '1'

$python = Get-Command python.exe -ErrorAction SilentlyContinue
if ($null -eq $python) {
    $python = Get-Command python -ErrorAction SilentlyContinue
}
if ($null -eq $python) {
    throw 'Python wurde nicht gefunden.'
}

$tests = @(Get-ChildItem -LiteralPath (Join-Path $RepositoryRoot 'tests') -Filter '*.py' -File | Sort-Object Name)
if ($tests.Count -eq 0) {
    throw 'Keine Python-Regressionstests gefunden.'
}

foreach ($test in $tests) {
    Write-Host "==> $($test.Name)"
    & $python.Source $test.FullName
    if ($LASTEXITCODE -ne 0) {
        throw "Test fehlgeschlagen: $($test.Name)"
    }
}

Write-Host "Alle $($tests.Count) Python-Testprogramme wurden bestanden."
