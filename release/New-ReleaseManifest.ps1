[CmdletBinding()]
param([Parameter(Mandatory=$true)][string]$Payload,[string]$Version='')
Set-StrictMode -Version Latest
$ErrorActionPreference='Stop'
if ([string]::IsNullOrWhiteSpace($Version)) {
    $repoRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
    $Version = (& (Join-Path $repoRoot 'scripts\Get-RepositoryVersion.ps1') -RepositoryRoot $repoRoot).Product
}
$root=(Resolve-Path -LiteralPath $Payload).Path.TrimEnd('\')
$manifestPath=[IO.Path]::GetFullPath((Join-Path $root 'release-manifest.json'))
$seen=[Collections.Generic.HashSet[string]]::new([StringComparer]::OrdinalIgnoreCase)
$files=@(Get-ChildItem -LiteralPath $root -File -Recurse | Where-Object {
    [IO.Path]::GetFullPath($_.FullName) -ne $manifestPath
} | Sort-Object FullName | ForEach-Object {
    if (($_.Attributes -band [IO.FileAttributes]::ReparsePoint) -ne 0) { throw "Reparse Point ist im Release-Payload nicht erlaubt: $($_.FullName)" }
    $relative=$_.FullName.Substring($root.Length).TrimStart('\','/').Replace('\','/')
    if(-not $seen.Add($relative)){throw "Doppelter Release-Pfad: $relative"}
    [ordered]@{path=$relative;sha256=(Get-FileHash -Algorithm SHA256 -LiteralPath $_.FullName).Hash.ToLowerInvariant();size=$_.Length}
})
[ordered]@{product='AstroFocus Studio';version=$Version;architecture='windows-x64';generatedUtc=[DateTime]::UtcNow.ToString('o');files=$files} | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath $manifestPath -Encoding UTF8
