AstroFocus Studio 3.8.8 – Security-Cookie-Startup-Patch

Dieser Patch behebt den Windows-Fast-Fail 0xC0000409 beim Health-Check.

Anwendung:
1. ZIP lokal entpacken.
2. Den gesamten Inhalt in die Wurzel des bestehenden Repositorys kopieren.
3. Vorhandene Dateien ersetzen und die Verzeichnisstruktur beibehalten.
4. Alle Dateien committen und pushen.
5. Einen neuen Workflow-Lauf für den neuen Commit abwarten.

Wichtig: Nicht nur einzelne Quelldateien auswählen. Der gemeinsame Einstieg,
alle Buildskripte und die aktualisierten Regressionstests gehören zusammen.
