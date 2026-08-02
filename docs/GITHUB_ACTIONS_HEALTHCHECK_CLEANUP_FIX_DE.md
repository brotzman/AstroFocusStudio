# GitHub Actions: Engine-Health-Check 20 und hängende Fehlerbereinigung

Der Windows-Runner installierte das Burn-Bundle erfolgreich und bestätigte alle
installierten SHA-256-Prüfsummen. Danach beendete sich `AstroFocusEngine.exe
--health-check` mit Exitcode 20. Die anschließende Fehlerbereinigung versuchte das
vom Burn-Bundle installierte Produkt direkt über die MSI-Datei zu entfernen und
blockierte bis zum Timeout.

## Health-Check

Der Engine-Health-Check startete intern nochmals Kamera- und Fokussiererhost und
fasste Schreib-, Datei-, Prozessstart-, Timeout- und Hostfehler gemeinsam als
Exitcode 20 zusammen. Diese Verschachtelung wurde entfernt.

Der CI-Test startet jetzt die beiden Hosts und die Engine als drei unabhängige
Prüfungen. Der Engine-Check prüft nur noch seinen eigenen Installations- und
Datenpfad. Seine Diagnosecodes sind:

- 21: Anwendungs- oder Datenpfad nicht initialisiert
- 22: Kamerahost fehlt
- 23: Fokussiererhost fehlt
- 24: temporäre Datei im Benutzerdatenordner kann nicht erstellt werden
- 25: temporäre Datei kann nicht vollständig geschrieben werden

Außerdem wertet die Engine `--health-check` jetzt als exaktes
Kommandozeilentoken aus und verwirft beschädigte oder doppelte Angaben.

## Fehlerbereinigung

Ein durch Burn installiertes Produkt wird bei einem fehlgeschlagenen Smoke-Test
zuerst mit demselben Bundle und `/uninstall` entfernt. Erst wenn danach noch ein
Installationsordner vorhanden ist, folgt eine zeitlich begrenzte direkte
MSI-Deinstallation als Fallback. Vorher werden nur die bekannten AstroFocus-
Prozesse beendet.

Die Cleanup-Protokolle heißen:

- `cleanup-bundle-uninstall.log`
- `cleanup-msi-uninstall.log`
- `installer-smoke.log`
