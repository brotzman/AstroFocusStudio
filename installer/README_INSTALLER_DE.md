# Installer, Reparatur und Rollback – 3.8.8

## Installation des unsignierten Entwicklungsbuilds

1. Das ZIP **vollständig in einen normalen Ordner entpacken**. Nicht direkt aus der ZIP-Vorschau starten.
2. `Install-Development.cmd` doppelt anklicken.
3. Die Windows-Administratorabfrage bestätigen.
4. Auf den abschließenden Erfolgs- oder Fehlerdialog warten.

Alternativ kann `AstroFocusSetup.exe` direkt gestartet werden. Wenn die Datei `UNSIGNED_DEVELOPMENT_BUILD.txt` daneben liegt, erkennt der Launcher den Entwicklungsmodus automatisch.

Der Launcher verwendet den festen Pfad von Windows PowerShell 5.1, behandelt die Download-Markierung des ausdrücklich unsignierten Prüfbundles und zeigt Start-, UAC-, PowerShell- und Installationsfehler sichtbar an. Das Diagnoseprotokoll befindet sich unter:

`C:\ProgramData\AstroFocusStudio\Logs\Installer.log`

Das Setup prüft das SHA-256-Payloadmanifest, verhindert parallele Installer- und Updaterinstanzen, beendet ausschließlich AstroFocus-Prozesse aus dem Installationsordner, sichert eine bestehende Installation, installiert nach `Program Files`, führt Health-Checks aus und stellt bei Fehlern die Vorgängerversion wieder her. Profile und Protokolle bleiben erhalten.

## Hinweis

Dieses Bundle ist nicht öffentlich signiert. Für eine öffentliche Freigabe müssen Binärdateien, Skripte, MSI und Setup-EXE signiert und zeitgestempelt werden.

## Korrektur für Windows PowerShell 5.1

Der Payloadpfad wird erst nach der PowerShell-Parameterbindung aus dem tatsächlichen Skriptordner bestimmt. Dadurch tritt der frühere `Join-Path`-Abbruch mit leerem `$PSScriptRoot` nicht mehr auf. Dieser Fehler geschah noch vor der Protokollinitialisierung und konnte deshalb kein `Installer.log` erzeugen.
