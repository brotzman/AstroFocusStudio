AstroFocus Studio 3.9.0 – Patch für die Speicherung des Farbschemas

Den Inhalt dieses Patch-ZIPs in das Hauptverzeichnis des aktuellen 3.9.0-
GitHub-Repositorys kopieren und vorhandene Dateien ersetzen.

Anschließend:

  git add -A
  git commit -m "Fix per-user theme settings persistence"
  git push

Die Einstellung wird danach unter folgendem Pfad gespeichert:

  %LOCALAPPDATA%\AstroFocusStudio\AstroFocusUiSettings.ini
