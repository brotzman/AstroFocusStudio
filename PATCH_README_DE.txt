AstroFocus Studio 3.8.8 – GitHub Actions MSI-Runner-Isolationsfix

Das ZIP im Hauptverzeichnis des bestehenden Repositorys entpacken und vorhandene
Dateien ersetzen. Danach einen neuen Commit erzeugen und pushen. Nicht den alten
fehlgeschlagenen Workflow erneut ausführen, weil ein Re-run den alten Commit nutzt.

Die Änderung trennt Burn-Bundle- und MSI-Tests auf zwei frische Windows-Runner.
