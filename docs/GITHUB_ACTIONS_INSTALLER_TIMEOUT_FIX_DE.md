# GitHub Actions: Installer-Smoke-Test überschritt 45 Minuten

Die hochgeladenen Protokolle zeigen, dass Build, Python-Tests, WiX-Paketbau und
Bundle-Installation erfolgreich abgeschlossen wurden. `bundle-install.log` endet mit
Exitcode 0. Danach entstanden weder Reparatur- noch Deinstallationsprotokolle.

Ursache des CI-Hängers war der Einsatz von `Start-Process -Wait`. Unter Windows kann
PowerShell dabei nicht nur auf den direkt gestarteten Burn-/MSI-Prozess, sondern auf
dessen verbleibenden Prozessbaum warten. Das ist für Installer-Smoke-Tests ungeeignet
und kann den Job bis zum globalen 45-Minuten-Limit blockieren.

`Test-GitHubInstaller.ps1` verwendet jetzt einen direkten
`System.Diagnostics.Process`-Handle, wartet mit einem festen Timeout nur auf diesen
Prozess, beendet bei Zeitüberschreitung den Prozessbaum und protokolliert jede Phase in
`artifacts/test-logs/installer-smoke.log`.
