# GitHub-Release und Desktopverknüpfung

## Manuelle Veröffentlichung

Der Workflow kann normal zum reinen Bauen und Testen gestartet werden. Für eine Veröffentlichung wird unter **Run workflow** `publish_release` aktiviert und `release_tag` auf `v3.8.8` gesetzt. Alle Build-, Sanitizer-, Bundle- und MSI-Tests müssen erfolgreich sein. Danach prüft der Release-Job die SHA-256-Datei, erzeugt einen fehlenden Tag am getesteten Commit und erstellt oder aktualisiert das GitHub Release.

Ein abweichender Tag wird abgelehnt, damit ein 3.8.8-Paket nicht versehentlich unter einer anderen Versionsnummer veröffentlicht wird. Ein normal gepushter Tag `v3.8.8` löst denselben geprüften Releasepfad aus.

## Desktopverknüpfung

`installer/wix/Package.wxs` enthält eine eigene MSI-Komponente im WiX-5-konformen `DesktopFolder`. Da das Paket mit `Scope="perMachine"` installiert wird, leitet Windows Installer diesen Ordner auf den All-Users-/öffentlichen Desktop um. Dadurch wird `AstroFocus Studio.lnk` für alle Benutzer angelegt. Die Verknüpfung zeigt auf `[INSTALLFOLDER]AstroFocusStudio.exe`, nutzt den Installationsordner als Arbeitsverzeichnis und übernimmt das Programmsymbol.

Die separaten Burn- und MSI-Smoke-Tests kontrollieren nach Installation und Reparatur:

- Existenz der Verknüpfung,
- Zielpfad,
- Arbeitsverzeichnis.

Nach der Deinstallation darf die Verknüpfung nicht mehr vorhanden sein.
