[CmdletBinding()]
param([Parameter(Mandatory=$true)][string]$RepositoryRoot)
Set-StrictMode -Version Latest
$versionPath = Join-Path ([IO.Path]::GetFullPath($RepositoryRoot)) 'VERSION'
if (-not (Test-Path -LiteralPath $versionPath -PathType Leaf)) { throw "VERSION file is missing: $versionPath" }
$text = (Get-Content -LiteralPath $versionPath -Raw -Encoding UTF8).Trim()
if ($text -notmatch '^(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)$') { throw "Invalid semantic version in VERSION: $text" }
[pscustomobject]@{
    Product = $text
    Bundle = "$text.0"
    Tag = "v$text"
    FileToken = $text.Replace('.','_')
}
