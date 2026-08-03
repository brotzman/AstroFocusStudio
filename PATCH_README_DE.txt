AstroFocus Studio 3.9.0 – Patch für supersedierte Versionsdateien

1. Den Inhalt dieses ZIPs in das Hauptverzeichnis des bestehenden
   3.9.0-Repositorys kopieren und vorhandene Dateien ersetzen.
2. Cleanup-Legacy-Version-Files.cmd ausführen.
3. Danach im Repository ausführen:

   git add -A
   git commit -m "Remove superseded version files"
   git push

Wichtig: git add -A zeichnet auch die Löschung umbenannter Vorgängerdateien auf.
Der GitHub-Workflow bereinigt diese exakt bekannten Altdateien zusätzlich in
seinem temporären Arbeitsverzeichnis und führt nur die aktuelle Testsuite aus.
