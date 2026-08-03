AstroFocus Studio 3.9.0 – UI-Startabsturz-Fix

Den Inhalt dieses ZIPs in das Hauptverzeichnis des bestehenden 3.9.0-GitHub-Repositorys kopieren und vorhandene Dateien ersetzen.

Danach:
  git add -A
  git commit -m "Fix frontend crash during first UI status update"
  git push

Der Fix entfernt nicht unterstützte %+d-Formatierung aus USER32-wsprintfW, baut den Nachführungsstatus begrenzt ohne wsprintfW auf und ergänzt Regressionstests.
