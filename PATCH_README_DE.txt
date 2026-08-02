AstroFocus Studio 3.8.8 – GitHub Actions Preflight-Fix

Ursache:
- .gitattributes und .gitignore wurden fälschlich als zwingende Builddateien behandelt.
- Das Diagnoseverzeichnis wurde erst nach der Vorabprüfung angelegt.
- Dadurch scheiterte der Build unnötig und der Log-Upload meldete zusätzlich, dass keine Dateien vorhanden seien.

Installation des Patches:
1. ZIP lokal entpacken.
2. Den Inhalt mit unveränderter Ordnerstruktur in die Wurzel des GitHub-Repositorys kopieren.
3. Vorhandene Dateien ersetzen.
4. Committen und pushen.
5. Den Workflow erneut starten.

Die beiden Dotfiles sind weiterhin im vollständigen Repository enthalten, fehlen sie aber beim Webupload, wird nur noch eine Warnung ausgegeben.
