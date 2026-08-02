# GitHub Actions: Build-GitHubArtifacts.ps1 fehlt

Die Meldung

```text
.\scripts\Build-GitHubArtifacts.ps1 is not recognized
```

bedeutet, dass die Datei `scripts/Build-GitHubArtifacts.ps1` nicht im Commit enthalten war, den der Windows-Runner ausgecheckt hat. Das ist kein Compiler- oder WiX-Fehler.

Der korrigierte Workflow:

- prüft nach `actions/checkout` alle erforderlichen Builddateien,
- verankert Pfade an `GITHUB_WORKSPACE`,
- startet das Buildskript über einen absoluten Pfad mit Windows PowerShell 5.1,
- schreibt weiterhin `artifacts/test-logs/build-package.log`.

Beim Einspielen eines Patch-ZIPs muss der gesamte Ordner `scripts` übernommen werden. Insbesondere müssen diese Dateien im GitHub-Repository sichtbar sein:

```text
scripts/Build-GitHubArtifacts.ps1
scripts/Run-PythonTests.ps1
scripts/Test-GitHubInstaller.ps1
scripts/Run-NativeTests.sh
```
