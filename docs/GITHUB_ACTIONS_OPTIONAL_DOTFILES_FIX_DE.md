# GitHub Actions: optionale Dotfiles und Preflight-Protokoll

## Ursache

Der Windows-Job verlangte `.gitattributes` und `.gitignore` als zwingende Builddateien.
Beim Upload über die GitHub-Weboberfläche oder den Windows Explorer können versteckte Dateien jedoch leicht fehlen.
Diese beiden Dateien steuern Git- und Checkout-Verhalten, werden aber weder vom Compiler noch von WiX benötigt.

Zusätzlich wurde `artifacts/test-logs` erst nach der Repositoryprüfung erstellt. Schlug die Prüfung vorher fehl, konnte der anschließende Log-Upload kein Artefakt finden und erzeugte eine zweite, irreführende Fehlermeldung.

## Korrektur

- `.gitattributes` und `.gitignore` sind optionale Repository-Metadaten.
- Fehlen sie, wird eine Warnung ausgegeben; der Build läuft weiter.
- Echte Builddateien wie `Package.wxs`, `Bundle.wxs` und die Buildskripte bleiben zwingend.
- `artifacts/test-logs/preflight.log` wird vor der Repositoryprüfung angelegt.
- Der Log-Upload verwendet `if-no-files-found: warn`, damit er niemals den ursprünglichen Fehler verdeckt.
- Der Python-Vertragstest kann auch ohne beide Dotfiles ausgeführt werden.
