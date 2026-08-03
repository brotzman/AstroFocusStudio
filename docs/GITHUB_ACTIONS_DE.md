# Aufbau des GitHub-Actions-Workflows

## Job `native-tests`

Der Linux-Job kompiliert und startet diese drei Testprogramme mit ASan und UBSan:

- `tests/command_line_args_validation_390.cpp`
- `tests/frontend_logic_validation_390.cpp`
- `tests/actual_backend_validation_390.cpp`

Ein Fehler, Speicherzugriffsproblem oder undefiniertes Verhalten stoppt den Workflow,
bevor ein Windows-Paket gebaut wird.

## Job `windows-build`

Der Windows-2022-Job:

1. validiert sämtliche PowerShell-Dateien mit dem PowerShell-Parser,
2. kompiliert alle sieben Programme mit `/W4 /WX /O2 /GS`,
3. bestätigt für jede EXE Windows x64 und PE32+,
4. führt sämtliche Python-Vertrags- und Pakettests aus,
5. erzeugt einen frischen Payload und dessen SHA-256-Manifest,
6. installiert die festgelegte WiX-Version als lokales .NET-Tool,
7. erstellt MSI, Burn-Setup und portable ZIP-Datei,
8. stellt die fertig gebauten Release-Dateien und ein isoliertes Installer-Testpaket bereit,
9. lädt Build- und Python-Protokolle als eigene Artefakte hoch.

## Jobs `bundle-test` und `msi-test`

Zwei getrennte, frische Windows-Runner prüfen das Burn-Setup und das rohe MSI. Beide Jobs:

1. installieren das jeweilige Paket still,
2. verifizieren jede installierte Datei gegen das Payloadmanifest,
3. prüfen die automatische Verknüpfung `AstroFocus Studio.lnk` auf dem öffentlichen Desktop,
4. starten Kamera-Host-, Fokussierer-Host- und Engine-Health-Checks,
5. entfernen absichtlich eine Komponente und prüfen die Reparatur,
6. deinstallieren das Produkt und bestätigen, dass Programmordner und Desktopverknüpfung entfernt wurden.

## Job `release`

Der Release-Job läuft entweder bei einem Tag mit `v`-Präfix oder nach einem manuellen
`workflow_dispatch` mit aktivierter Option `publish_release`. Er lädt exakt das im
Windows-Job geprüfte Artefakt herunter, prüft `SHA256SUMS.txt` und erstellt oder
aktualisiert das GitHub Release. Bei manueller Veröffentlichung wird ein noch nicht
vorhandener Tag am getesteten Commit erzeugt. Der Tag muss exakt `v` plus
`PRODUCT_VERSION` entsprechen, bei 3.9.0 also `v3.9.0`.

## Nicht abgedeckt

GitHub-gehostete Runner haben keinen Zugriff auf die reale ToupTek-Kamera, den
Celestron-Fokussierer oder lokal installierte ASCOM-Treiber. Diese Prüfungen müssen auf
einem realen Windows-System oder später auf einem gesicherten selbst gehosteten Runner
erfolgen.
