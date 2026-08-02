[CmdletBinding()]
param([Parameter(Mandatory=$true)][string]$Path,[string]$ExpectedPublisher='Thomas Brotze',[switch]$AllowUnsignedDevelopment)
Set-StrictMode -Version Latest;$ErrorActionPreference='Stop'
$failed=@()
foreach($file in Get-ChildItem -LiteralPath $Path -Recurse -File | Where-Object Extension -in '.exe','.dll','.msi','.msix','.ps1'){
 $sig=Get-AuthenticodeSignature -LiteralPath $file.FullName
 if($AllowUnsignedDevelopment -and $sig.Status -eq 'NotSigned'){continue}
 if($sig.Status -ne 'Valid' -or ($ExpectedPublisher -and $sig.SignerCertificate.Subject -notlike "*$ExpectedPublisher*")){$failed+=$file.FullName}
}
if($failed.Count){throw "Ungültige/fehlende Signaturen:`n$($failed -join "`n")"}
Write-Host 'Alle Release-Signaturen sind gültig.'
