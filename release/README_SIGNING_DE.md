# Produktionssignierung

Die Quellpakete enthalten **keinen privaten Schlüssel**. Für ein Produktionsrelease werden ein öffentlich vertrauenswürdiges Windows-Code-Signing-Zertifikat und ein getrennt verwahrter RSA-Schlüssel für Update-Manifeste benötigt.

Reihenfolge:
1. Release bauen und `release-manifest.json` erzeugen.
2. EXE/DLL/MSI und PowerShell-Werkzeuge mit `Sign-Release.ps1` signieren und RFC-3161-zeitstempeln.
3. Setup-ZIP erzeugen und SHA-256 berechnen.
4. Update-Manifest mit `New-UpdateManifest.ps1` signieren.
5. Signaturen mit `Verify-Release.ps1` prüfen.
6. Erst danach veröffentlichen.

Der private Schlüssel darf weder im Repository noch im Quell- oder Windows-Archiv liegen. Empfohlen werden Hardwaretoken, HSM oder ein geschützter Signing-Runner.
