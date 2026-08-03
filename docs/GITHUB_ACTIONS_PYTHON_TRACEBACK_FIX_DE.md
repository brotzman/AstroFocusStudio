# GitHub Actions: Python-Traceback im Windows-Build

## Beobachtung

Der Windows-x64-Build erzeugte alle sieben Programme erfolgreich. Anschließend brach
`github_workflow_validation.py` unmittelbar nach seinem Start ab. Windows
PowerShell zeigte nur die erste Zeile `Traceback (most recent call last):` und wandelte
diese wegen `$ErrorActionPreference = 'Stop'` in einen `NativeCommandError` um.

## Korrekturen

- `Run-PythonTests.ps1` startet Python über `Start-Process` und leitet Standardausgabe
  und Standardfehler in getrennte Dateien um. Dadurch bleibt ein vollständiger
  Python-Traceback erhalten.
- Alle Python-Ausgaben werden zusätzlich in
  `artifacts/test-logs/python-tests.log` gespeichert.
- `github_workflow_validation.py` prüft alle erforderlichen Workflow- und
  WiX-Dateien vor dem Einlesen und meldet fehlende Dateien ohne Python-Traceback.
- UTF-8-Dateien mit und ohne BOM werden akzeptiert.
- Der Checkout-Preflight prüft jetzt zusätzlich `Package.wxs`, `Bundle.wxs`,
  `.gitattributes`, `.gitignore` und den Workflow-Vertragstest.

## Ergebnis

Fehlt künftig eine Datei im GitHub-Commit, wird sie bereits vor dem Build namentlich
aufgeführt. Scheitert ein Python-Test aus einem anderen Grund, enthält das hochgeladene
Installer-Log-Artefakt den vollständigen Inhalt von `python-tests.log`.
