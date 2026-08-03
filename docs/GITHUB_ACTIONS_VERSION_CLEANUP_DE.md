# GitHub Actions: alte 3.8.8-Testdateien nach Versionswechsel

Beim Ersetzen eines Repository-Inhalts bleiben umbenannte Dateien im Git-Index erhalten,
wenn sie nicht mit `git add -A` beziehungsweise `git rm` gelöscht werden. Dadurch können
alte `_388`-Tests neben den aktuellen `_390`-Tests liegen.

Version 3.9.0 verwendet deshalb zwei Schutzebenen:

1. `scripts/remove_legacy_version_files.py` entfernt im CI-Arbeitsverzeichnis nur eine
   explizite Liste supersedierter 3.8.8-Dateien.
2. `scripts/Run-PythonTests.ps1` führt ausschließlich `*_390.py` aus und startet den
   Versionskonsistenztest zuerst.

Für die dauerhafte Bereinigung des Git-Repositorys lokal ausführen:

```powershell
python .\scripts\remove_legacy_version_files.py --root .
git add -A
git commit -m "Remove superseded 3.8.8 version files"
git push
```
