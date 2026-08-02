AstroFocus Studio 3.8.8 – GitHub-Patch für fehlende Payload-Quelldateien

1. Dieses ZIP lokal entpacken.
2. Den gesamten Inhalt in das Hauptverzeichnis des GitHub-Repositories kopieren.
3. Vorhandene Dateien ersetzen und die Ordnerstruktur beibehalten.
4. Prüfen, dass KNOWN_LIMITATIONS_3_8_8.txt direkt im Repository-Hauptverzeichnis liegt.
5. Anschließend ausführen:

   git add -A
   git commit -m "Restore installer payload sources and validate them before build"
   git push

Der Patch enthält vorsorglich alle nicht kompilierten Quelldateien, die in das MSI-Payload übernommen werden. Dadurch folgt nicht nach der reparierten Datei sofort der nächste Abbruch wegen einer weiteren fehlenden Payload-Datei.
