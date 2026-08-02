AstroFocus Studio 3.8.8 – Update-Schlüssel

update-public-key.cer enthält ausschließlich einen öffentlichen Entwicklungs-
Prüfschlüssel. Der private Schlüssel wurde nicht gespeichert und ist nicht im
Quell- oder Releasepaket enthalten.

Vor einem Produktionsrelease:
1. eigenes RSA-Code-/Update-Signing-Zertifikat erzeugen oder Signierdienst nutzen,
2. update-public-key.cer durch den öffentlichen Produktionsschlüssel ersetzen,
3. dessen SHA-256-Fingerabdruck in installer/AstroFocusSetup.ps1 eintragen,
4. UNSIGNED_DEVELOPMENT_BUILD.txt aus Bundle und Payload entfernen,
5. Manifest, EXE, DLL, MSI und Bootstrapper signieren und verifizieren.
