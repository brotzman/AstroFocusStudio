# Benutzerbezogene Speicherung des Farbschemas – AstroFocus Studio 3.9.0

Das Farbschema wird nicht mehr neben der installierten EXE gespeichert. Dieser
Ordner liegt bei einer normalen Installation unter `C:\Program Files` und ist
für Standardbenutzer nicht beschreibbar.

Die Einstellung wird jetzt pro Benutzer unter folgendem Pfad gespeichert:

```text
%LOCALAPPDATA%\AstroFocusStudio\AstroFocusUiSettings.ini
```

Falls `LOCALAPPDATA` ausnahmsweise nicht verfügbar ist, wird ein eigener
AstroFocusStudio-Unterordner im temporären Benutzerverzeichnis verwendet.

Der Schreibvorgang erfolgt atomar:

1. Schreiben in eine prozessspezifische temporäre Datei,
2. Flush der Dateidaten,
3. Ersetzen der endgültigen Datei mit `MoveFileExW`,
4. Entfernen nur der temporären Datei bei einem Fehler.

Eine vorhandene alte Einstellungsdatei neben der EXE wird einmalig gelesen und
anschließend in den neuen Benutzerpfad migriert. Ein Speicherfehler erzeugt
keinen störenden modalen Dialog mehr, sondern wird mit Pfad und Windows-
Fehlercode in `FrontendTrace.log` protokolliert.
