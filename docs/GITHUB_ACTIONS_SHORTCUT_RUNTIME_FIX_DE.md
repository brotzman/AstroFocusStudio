# GitHub Actions: Desktopverknüpfung robust prüfen

Die MSI- und Bundle-Protokolle bestätigen, dass Windows Installer die Verknüpfung unter
`C:\Users\Public\Desktop\AstroFocus Studio.lnk` erzeugt und bei der Deinstallation entfernt.
Der Workflow scheiterte erst beim anschließenden COM-Auslesen der Verknüpfung.

Der Laufzeittest wurde deshalb robuster gemacht:

- bis zu 10 Sekunden auf die veröffentlichte `.lnk`-Datei warten;
- Ziel und Arbeitsverzeichnis vor dem Vergleich kanonisieren;
- abschließende Verzeichnistrennzeichen ignorieren;
- `WScript.Shell` verwenden und bei leerem Ziel auf `Shell.Application` zurückfallen;
- ein von der CI-Shell nicht geliefertes Arbeitsverzeichnis nur protokollieren;
- das in WiX fest authorisierte `WorkingDirectory="INSTALLFOLDER"` weiterhin statisch prüfen;
- Rohwerte und Fehler vollständig in `installer-smoke.log` schreiben;
- das Smoke-Log durchgehend als UTF-8 statt gemischt als UTF-8/UTF-16 schreiben.

Die Verknüpfung selbst wurde nicht verändert. Die Installerprotokolle zeigen bereits die
korrekte Erstellung mit Ziel `AstroFocusStudio.exe` und Arbeitsverzeichnis im Installationsordner.
