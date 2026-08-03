# GitHub Actions: Payload-Preflight synchronisiert

Der Windows-Build war erfolgreich, aber `github_workflow_validation_390.py` meldete drei fehlende Preflight-Einträge. Ursache war ein gemischter Repository-Stand: Der Vertragstest stammte aus dem neueren Patch, während `.github/workflows/windows-build.yml` noch aus einem älteren Stand kam.

Die Workflow-Vorabprüfung enthält jetzt verbindlich:

- `KNOWN_LIMITATIONS_3_9_0.txt`
- `UNSIGNED_DEVELOPMENT_BUILD.txt`
- `updater\update-public-key.cer`

Der Vertragstest wertet zusätzlich den gesamten `$requiredFiles`-Block aus, damit Workflow und aktuelle Packaging-Quellen nicht erneut auseinanderlaufen.
