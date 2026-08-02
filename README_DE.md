# AstroFocus Studio 3.8.8

AstroFocus Studio ist eine native Windows-x64-Anwendung für Live-Fokus, statistisch ausgewerteten Autofokus, Bahtinov-Unterstützung, Fokusautomation und reproduzierbare Simulatorprüfungen.

## Korrekturen in 3.8.8

### Lokale API und Eingabevalidierung

- Abfrageparameter werden nur noch an echten `?`-/`&`-Grenzen erkannt. Ein Parameter wie `xname=` kann nicht mehr versehentlich als `name=` behandelt werden.
- URL-kodierte Texte werden vollständig oder gar nicht übernommen. NUL- und Steuerzeichen, fehlerhafte `%xx`-Sequenzen, ungültiges oder unvollständiges UTF-8 und überlange Werte werden abgelehnt.
- Zahlenparameter bleiben bereichs- und überlaufsicher.

### Fokussierer und Gerätehosts

- Die Fokussierer-Konfiguration ist während Autofokus, Schritt-Assistent, Backlash-Kalibrierung und manueller Motorfahrt gesperrt.
- Der tatsächliche Bewegungszustand des Fokussierers wird von der Engine an die Oberfläche übertragen und bei der Bedienfreigabe berücksichtigt.
- Kamera- und Fokussiererhosts lesen `--pipe` und `--health-check` als exakte Kommandozeilentoken. Teiltreffer, fehlende Werte, offene Anführungszeichen und abgeschnittene Pipe-Namen werden verworfen.
- Die zuvor korrigierte 24-Byte-Windows-x64-`VARIANT`-ABI im Fokussierer-Setup-Helfer bleibt durch Compiler- und Laufzeittests abgesichert.

### Standardverhalten des Hauptfensters

- Beim Minimieren bleibt AstroFocus Studio als normale Schaltfläche in der Windows-Taskleiste sichtbar.
- Das Hauptfenster wird nicht mehr verborgen oder in den Infobereich verschoben und lässt sich über die Taskleiste normal wiederherstellen und maximieren.

### Installer und Updater

- Eine fehlende oder beschädigte installierte `release-manifest.json` wird nicht mehr als gebündelte Programmversion ausgegeben. Der Updater markiert den Zustand als unbekannt und fordert Reparatur oder Rollback.
- Installer und Updater verhindern parallele Instanzen derselben Wartungsoperation über benannte Mutex-Sperren.
- Updatepakete werden weiterhin über HTTPS, RSA-signiertes Manifest, SHA-256, Authenticode-Herausgeber, sichere ZIP-Extraktion, Health-Check und Rollback abgesichert.

## Sichere Hardwarekommunikation

ASCOM-Kamera und ASCOM-Fokussierer laufen in getrennten Hostprozessen. Die Engine kommuniziert über lokale Named Pipes mit Protokollversion, Vorgangs-ID und Deadline. Nach einer nicht bestätigten Fokusbewegung gilt die Position als unbekannt; weitere automatische Bewegungen bleiben gesperrt, bis die Position sicher neu bestimmt wurde.

## Entwicklungsstatus

Das enthaltene Setup ist nicht öffentlich signiert. Eine Produktionsfreigabe benötigt ein eigenes Code-Signing-Zertifikat beziehungsweise einen geschützten Signierdienst sowie einen eingetragenen Update-Zertifikat-Fingerabdruck.

Der GitHub-Actions-Workflow führt einen vollständigen Windows-x64-Build aus und prüft Burn-Bundle und rohes MSI anschließend auf zwei getrennten, frischen Windows-2022-Runnern. Beide Pfade umfassen stille Installation, Reparatur, Health-Checks und Deinstallation. Diese automatisierten Prüfungen ersetzen keine Tests auf dem realen Zielsystem. Vor unbeaufsichtigtem Einsatz müssen unter Windows 11 insbesondere bestätigt werden:

- ASCOM-Chooser und Treiber-`SetupDialog`,
- Verbindung, Bewegung, Halt und Wiederverbindung des konkreten Fokussierers,
- Verbindung und Livebild der realen ToupTek-Kamera,
- USB-Trennung während Belichtung oder Motorfahrt,
- Standby/Fortsetzung,
- Installation, Reparatur, Update und Rollback mit UAC und Registry.

## Bereinigtes Quellpaket

Dieses Quellpaket enthält ausschließlich den Stand 3.8.8. Historische Layoutbilder,
alte Prüfberichte, Teststände früherer Versionen und kompilierte EXE-Dateien wurden
entfernt. Die sieben fertigen Programme, das MSI, das Burn-Setup und die portable Version werden
nach erfolgreichem GitHub-Actions-Lauf als geprüftes Workflow-Artefakt bereitgestellt.

Build unter Linux mit LLVM/Clang:

```bash
./build-windows-x64.sh
```

Build unter Windows mit LLVM/Clang im Developer Command Prompt:

```cmd
build-all-windows-x64.bat
```

Beide Sammel-Builds erstellen alle sieben Windows-x64-Programme.

Die aktuellen 3.8.8-Prüfungen befinden sich gesammelt unter `tests`.


## GitHub Repository und Installerbuild

Der vorbereitete Workflow liegt unter `.github/workflows/windows-build.yml`. Er baut
die sieben Programme auf `windows-2022`, erzeugt mit WiX ein MSI und ein Burn-Setup
und führt echte stille Installations-, Reparatur- und Deinstallationstests auf getrennten, frischen Windows-Runnern aus.
Die Upload-Anleitung steht in `docs/GITHUB_UPLOAD_DE.md`.

### CI-Health-Checks und Fehlerbereinigung

Die GitHub-Prüfung startet Kamera-Host, Fokussierer-Host und Engine als drei
getrennte Health-Checks. Burn-Bundle und rohes MSI werden nicht mehr nacheinander auf
demselben Windows-System geprüft, sondern in zwei unabhängigen Jobs auf frischen
Runnern. Dadurch kann ein von Burn zurückgelassener Windows-Installer- oder
Neustartstatus die direkte MSI-Installation nicht blockieren. Details stehen in
`docs/GITHUB_ACTIONS_MSI_RUNNER_ISOLATION_FIX_DE.md`.
