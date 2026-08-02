AstroFocus Studio 3.8.8 – GitHub-Release- und Desktopverknüpfungs-Patch

1. Dieses ZIP lokal entpacken.
2. Den Inhalt in das Hauptverzeichnis des vorhandenen Repositorys kopieren.
3. Vorhandene Dateien ersetzen; die Ordnerstruktur einschließlich .github beibehalten.
4. Danach committen und pushen:

   git add -A
   git commit -m "Add manual tag release and desktop shortcut"
   git push

Neues Verhalten:
- Normaler Push: Build und Tests, aber kein Release.
- Push des Tags v3.8.8: Nach allen Tests wird das GitHub Release veröffentlicht.
- Manueller Start unter Actions mit publish_release=true und release_tag=v3.8.8:
  Nach allen Tests wird ein fehlender Tag am geprüften Commit erzeugt und das Release
  erstellt beziehungsweise aktualisiert.
- MSI und Setup legen AstroFocus Studio.lnk auf dem öffentlichen Windows-Desktop an.
- Bundle- und MSI-Smoke-Tests prüfen Verknüpfung, Reparatur und Entfernung.
