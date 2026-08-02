[CmdletBinding(DefaultParameterSetName='Store')]
param(
 [Parameter(Mandatory=$true)][string]$Path,
 [Parameter(Mandatory=$true,ParameterSetName='Store')][string]$Thumbprint,
 [Parameter(Mandatory=$true,ParameterSetName='Pfx')][string]$PfxPath,
 [Parameter(Mandatory=$true,ParameterSetName='Pfx')][securestring]$PfxPassword,
 [string]$TimestampUrl='http://timestamp.digicert.com')
Set-StrictMode -Version Latest
$ErrorActionPreference='Stop'

if(-not (Test-Path -LiteralPath $Path)){throw "Pfad nicht gefunden: $Path"}
$files=@(Get-ChildItem -LiteralPath $Path -Recurse -File | Where-Object Extension -in '.exe','.dll','.msi','.msix','.ps1')
if($files.Count -eq 0){throw 'Keine signierbaren Dateien gefunden.'}

$cert=$null
$plainPassword=$null
try {
 if($PSCmdlet.ParameterSetName -eq 'Store'){
   $normalized=($Thumbprint -replace '\s','').ToUpperInvariant()
   $cert=Get-ChildItem Cert:\CurrentUser\My,Cert:\LocalMachine\My |
     Where-Object { ($_.Thumbprint -replace '\s','').ToUpperInvariant() -eq $normalized } |
     Select-Object -First 1
 } else {
   if(-not (Test-Path -LiteralPath $PfxPath)){throw "PFX-Datei nicht gefunden: $PfxPath"}
   $cert=[Security.Cryptography.X509Certificates.X509Certificate2]::new(
     $PfxPath,$PfxPassword,[Security.Cryptography.X509Certificates.X509KeyStorageFlags]::EphemeralKeySet)
 }
 if($null -eq $cert -or -not $cert.HasPrivateKey){throw 'Code-Signing-Zertifikat mit privatem Schlüssel nicht gefunden.'}

 foreach($file in $files){
   if($file.Extension -eq '.ps1'){
     $result=Set-AuthenticodeSignature -LiteralPath $file.FullName -Certificate $cert -TimestampServer $TimestampUrl -HashAlgorithm SHA256
     if($result.Status -notin 'Valid','NotSigned'){throw "PowerShell-Signatur fehlgeschlagen: $($file.FullName) ($($result.Status))"}
   } elseif($PSCmdlet.ParameterSetName -eq 'Store') {
     & signtool.exe sign /fd SHA256 /td SHA256 /tr $TimestampUrl /sha1 $cert.Thumbprint $file.FullName
     if($LASTEXITCODE -ne 0){throw "SignTool fehlgeschlagen: $($file.FullName)"}
   } else {
     $bstr=[Runtime.InteropServices.Marshal]::SecureStringToBSTR($PfxPassword)
     try {$plainPassword=[Runtime.InteropServices.Marshal]::PtrToStringBSTR($bstr)}
     finally {[Runtime.InteropServices.Marshal]::ZeroFreeBSTR($bstr)}
     & signtool.exe sign /fd SHA256 /td SHA256 /tr $TimestampUrl /f $PfxPath /p $plainPassword $file.FullName
     if($LASTEXITCODE -ne 0){throw "SignTool fehlgeschlagen: $($file.FullName)"}
     $plainPassword=$null
   }
 }
} finally {
 $plainPassword=$null
 if($cert -and $cert -is [IDisposable]){$cert.Dispose()}
}
