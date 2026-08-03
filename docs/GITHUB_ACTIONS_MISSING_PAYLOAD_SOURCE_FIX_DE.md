# GitHub Actions: fehlende Payload-Quelldatei

Der Windows-Build konnte alle sieben Programme erzeugen, brach aber beim Zusammenstellen des Installer-Payloads ab, weil `KNOWN_LIMITATIONS_3_9_0.txt` im ausgecheckten Commit fehlte.

Die Datei ist kein historischer Testrest: Sie ist Bestandteil des aktuellen 3.9.0-Payloads und wird von `installer/wix/Package.wxs` installiert.

Der Fix stellt die Datei wieder her und erweitert den CI-Preflight um sämtliche nicht kompilierten Payload-Quellen. `Build-GitHubArtifacts.ps1` prüft diese Eingaben nun außerdem vor dem Compilerstart, sodass unvollständige Uploads sofort und gesammelt gemeldet werden.
