[CmdletBinding()]
param(
 [Parameter(Mandatory=$true)][string]$Package,
 [Parameter(Mandatory=$true)][string]$PackageUrl,
 [Parameter(Mandatory=$true)][string]$Version,
 [Parameter(Mandatory=$true)][string]$SigningPfx,
 [Parameter(Mandatory=$true)][securestring]$PfxPassword,
 [string]$Channel='stable',[string]$MinimumSupportedVersion='3.8.8',[string]$Publisher='Thomas Brotze',
 [string]$Output='update-manifest.json')
Set-StrictMode -Version Latest;$ErrorActionPreference='Stop'
$sha=(Get-FileHash -Algorithm SHA256 -LiteralPath $Package).Hash.ToLowerInvariant()
$payload=@('AstroFocus Studio',$Channel,$Version,$PackageUrl,$sha,$Publisher,$MinimumSupportedVersion)-join "`n"
$cert=[Security.Cryptography.X509Certificates.X509Certificate2]::new($SigningPfx,$PfxPassword,[Security.Cryptography.X509Certificates.X509KeyStorageFlags]::EphemeralKeySet)
$rsa=[Security.Cryptography.X509Certificates.RSACertificateExtensions]::GetRSAPrivateKey($cert)
if($null -eq $rsa){throw 'Das Signierzertifikat enthält keinen RSA-Privatschlüssel.'}
try{$sig=$rsa.SignData([Text.Encoding]::UTF8.GetBytes($payload),[Security.Cryptography.HashAlgorithmName]::SHA256,[Security.Cryptography.RSASignaturePadding]::Pkcs1)}finally{$rsa.Dispose();$cert.Dispose()}
[ordered]@{product='AstroFocus Studio';channel=$Channel;version=$Version;minimumSupportedVersion=$MinimumSupportedVersion;packageUrl=$PackageUrl;sha256=$sha;publisher=$Publisher;signature=[Convert]::ToBase64String($sig)}|ConvertTo-Json|Set-Content -LiteralPath $Output -Encoding UTF8
