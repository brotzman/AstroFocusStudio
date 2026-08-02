# GitHub Actions: clang-cl-Fehler bei den Tool-Launchern

Der Windows-Build brach bei `AstroFocusUpdater.exe` mit folgender Meldung ab:

```text
clang-cl: error: cannot specify '/Foupdater_launcher.obj' when compiling multiple source files
```

Ursache war ein Präprozessorwert mit Leerzeichen (`AstroFocus Studio Updater` beziehungsweise
`AstroFocus Studio Setup`) direkt in der Batch-Befehlszeile. Die Windows-CMD-Argumentauswertung
zerlegte den Wert in mehrere Argumente; `clang-cl` interpretierte Teile davon als zusätzliche
Quelldateien.

Die Launcher-Konfiguration liegt jetzt in zwei kleinen C++-Wrapperdateien:

- `tools/updater_launcher.cpp`
- `tools/setup_launcher.cpp`

Jeder Compileraufruf verarbeitet dadurch genau eine Quelldatei und benötigt keine komplex
maskierten String-Makros in der Batch-Datei mehr. Der Linux-Cross-Build verwendet dieselben
Wrapper, damit beide Buildwege übereinstimmen.
