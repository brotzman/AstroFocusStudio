AstroFocus Studio 3.8.8 – Standardfenster-/Taskleisten-Patch

Dieses Patchpaket entfernt das bisherige "Minimieren in den Infobereich" des
Hauptfensters. Beim Minimieren bleibt AstroFocus Studio als normale Schaltfläche
in der Windows-Taskleiste sichtbar und kann von dort wiederhergestellt oder
maximiert werden.

Anwendung:
1. ZIP lokal entpacken.
2. Den gesamten Inhalt in das Hauptverzeichnis des GitHub-Repositorys kopieren.
3. Vorhandene Dateien ersetzen und die Ordnerstruktur beibehalten.
4. Commit und Push erstellen. Der vorhandene GitHub-Actions-Workflow baut danach
   MSI, Setup-EXE und portable Pakete neu.

Geänderte Programmlogik:
- kein ShowWindow(..., SW_HIDE) mehr im SIZE_MINIMIZED-Pfad
- keine Tray-Icon-Erzeugung beim Minimieren
- normale WS_OVERLAPPED-/Taskleisten-Semantik bleibt erhalten
- nicht mehr benötigte Tray-Implementierung aus dem Frontend entfernt
