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

## Generierte Prüfsummendateien

`SHA256SUMS.txt`, `SOURCE_SHA256SUMS.txt` und `release-manifest.json` gehören nicht
in das Repository-Hauptverzeichnis. Sie werden beim Paketbau neu erzeugt. Die
Bereinigung entfernt versehentlich eingecheckte Root-Kopien vor der
Versionsprüfung, damit alte Artefaktnamen keinen 3.9.0-Build blockieren.


## Alte Patch-Hinweise

Zusätzlich entfernt die Allowlist veraltete, nur für frühere Austauschpakete gedachte Root-Dateien `PATCH_README_DE.txt` und `PATCH_README.txt`. Diese Dateien sind keine Produktdokumentation und dürfen nicht in ein Release-Repository übernommen werden, da sie alte Versionsverweise enthalten können.
