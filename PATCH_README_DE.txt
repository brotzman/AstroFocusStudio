AstroFocus Studio 3.8.8 - GitHub Actions Patch: fehlendes Buildskript

Ursache:
Der GitHub-Commit enthielt scripts/Build-GitHubArtifacts.ps1 nicht am erwarteten Pfad.
Der Windows-Runner konnte deshalb den Build nicht starten.

Anwendung:
1. Dieses ZIP vollständig entpacken.
2. Den gesamten Inhalt in die Wurzel des GitHub-Repositorys kopieren.
3. Vorhandene Dateien ersetzen; Ordnerstruktur beibehalten.
4. Auf GitHub kontrollieren, dass diese Datei sichtbar ist:
   scripts/Build-GitHubArtifacts.ps1
5. Alle Dateien committen und den Workflow erneut starten.

Der Workflow prüft jetzt nach dem Checkout alle erforderlichen Builddateien,
verwendet GITHUB_WORKSPACE als absoluten Repositorypfad und startet das
Buildskript explizit über Windows PowerShell 5.1.
