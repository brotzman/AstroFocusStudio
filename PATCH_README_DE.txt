AstroFocus Studio 3.8.8 – Desktopverknüpfungs-Prüfung

Den Inhalt dieses Archivs in das Hauptverzeichnis des bestehenden GitHub-Repositorys kopieren.
Vorhandene Dateien ersetzen und die Ordnerstruktur beibehalten.

Geändert werden:
- scripts/Test-GitHubInstaller.ps1
- tests/desktop_shortcut_runtime_validation_388.py
- docs/GITHUB_ACTIONS_SHORTCUT_RUNTIME_FIX_DE.md

Danach:
  git add -A
  git commit -m "Make desktop shortcut smoke test robust"
  git push

Nicht den alten Workflow-Lauf erneut ausführen, sondern den Lauf des neuen Commits verwenden.
