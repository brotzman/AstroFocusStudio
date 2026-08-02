# Repository auf GitHub hochladen

Dieses Paket ist bereits als Repository-Wurzel vorbereitet. Besonders wichtig ist der
versteckte Ordner `.github`, denn darin befindet sich der Windows-Buildworkflow.

## Empfohlener Weg mit Git

1. Auf GitHub ein **leeres** Repository erstellen. Beim Erstellen weder README noch
   `.gitignore` noch Lizenz automatisch hinzufügen.
2. Dieses ZIP vollständig entpacken.
3. Im entpackten Stammordner ein Terminal öffnen.
4. Die folgenden Befehle ausführen und die Beispieladresse ersetzen:

```bash
git init
git add .
git commit -m "AstroFocus Studio 3.8.8"
git branch -M main
git remote add origin https://github.com/DEIN-NAME/DEIN-REPOSITORY.git
git push -u origin main
```

Danach startet unter **Actions** automatisch der Workflow
**Build and test Windows installer**.

## Download der Ergebnisse

Nach erfolgreichem Workflow:

1. GitHub-Repository öffnen.
2. **Actions** wählen.
3. Den neuesten erfolgreichen Lauf öffnen.
4. Unter **Artifacts** `AstroFocusStudio-3.8.8-Windows-x64` herunterladen.

Die Installerprotokolle liegen getrennt im Artefakt
`AstroFocusStudio-3.8.8-Installer-Logs`.

## GitHub Release erzeugen

Nach einem erfolgreichen normalen Build kann Version 3.8.8 als Tag veröffentlicht
werden:

```bash
git tag v3.8.8
git push origin v3.8.8
```

Der Release-Job prüft `SHA256SUMS.txt` und hängt die bereits im Windows-Job gebauten
Dateien an das GitHub Release an. Es findet kein zweiter, abweichender Release-Build
statt.

## Hinweise

- Das Repository enthält bewusst keine fertigen EXE- oder MSI-Dateien. Diese werden
  ausschließlich von GitHub Actions erzeugt.
- Der erste Build benötigt Internetzugriff auf NuGet, um die festgelegte WiX-Version
  und die dazugehörige Bal-Erweiterung zu laden.
- Die Pakete sind ohne hinterlegtes Code-Signing-Zertifikat unsigniert.
- Reale Kamera- und Fokussiererhardware kann auf dem GitHub-Runner nicht geprüft
  werden.
- Vor einer öffentlichen Veröffentlichung sollte eine passende `LICENSE` ergänzt
  werden; im bereitgestellten Quellcode war keine Lizenzdatei vorhanden.

## Unix-Dateirechte beim Webupload

Beim Hochladen einzelner Dateien über die GitHub-Weboberfläche kann das
Ausführungsbit von `.sh`-Dateien verloren gehen. Der Workflow ruft den nativen
Teststarter deshalb mit `bash ./scripts/Run-NativeTests.sh` auf und ist nicht vom
Dateimodus abhängig. Für spätere Änderungen ist ein normaler Git-Commit dennoch
vorzuziehen.
