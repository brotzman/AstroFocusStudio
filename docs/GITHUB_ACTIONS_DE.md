# Aufbau des GitHub-Actions-Workflows

## Job `native-tests`

Der Linux-Job kompiliert und startet diese drei Testprogramme mit ASan und UBSan:

- `tests/command_line_args_validation_388.cpp`
- `tests/frontend_logic_validation_388.cpp`
- `tests/actual_backend_validation_388.cpp`

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
8. installiert das Burn-Setup still,
9. verifiziert jede installierte Datei gegen das Payloadmanifest,
10. startet Engine-, Kamera-Host- und Fokussierer-Host-Health-Checks,
11. löscht absichtlich eine installierte Komponente und prüft die Reparatur,
12. deinstalliert das Bundle,
13. wiederholt Installation und Deinstallation direkt mit dem MSI,
14. lädt Release-Dateien und Installationsprotokolle als getrennte Artefakte hoch.

## Job `release`

Der Release-Job läuft ausschließlich bei Tags mit `v`-Präfix. Er lädt exakt das im
Windows-Job geprüfte Artefakt herunter, prüft `SHA256SUMS.txt` und erstellt oder
aktualisiert das GitHub Release.

## Nicht abgedeckt

GitHub-gehostete Runner haben keinen Zugriff auf die reale ToupTek-Kamera, den
Celestron-Fokussierer oder lokal installierte ASCOM-Treiber. Diese Prüfungen müssen auf
einem realen Windows-System oder später auf einem gesicherten selbst gehosteten Runner
erfolgen.
