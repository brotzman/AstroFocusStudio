AstroFocus Studio 3.9.0 – Patch für veraltete Root-Prüfsummen

Ursache:
Eine alte, bereits eingecheckte SHA256SUMS.txt aus Version 3.8.8 wurde vom
Versionskonsistenztest gefunden. Diese Datei ist ein generiertes Release-Artefakt
und gehört nicht in den Repository-Stamm.

Anwendung:
1. Den Inhalt dieses ZIPs in das Hauptverzeichnis des Repositorys kopieren.
2. Vorhandene Dateien ersetzen.
3. Cleanup-Legacy-Version-Files.cmd ausführen.
4. Danach unbedingt ausführen:

   git add -A
   git commit -m "Remove stale generated checksum artifacts"
   git push

Die Bereinigung entfernt im Repository-Stamm nur diese explizit erlaubten
generierten Dateien:
- SHA256SUMS.txt
- SOURCE_SHA256SUMS.txt
- release-manifest.json

Die beim Build unter dist erzeugten aktuellen 3.9.0-Dateien werden nicht entfernt.
