# GitHub Actions: Native Sanitizer Tests – Exitcode 127

Exitcode 127 bedeutet, dass die Shell einen benötigten Befehl oder ein gestartetes
Programm nicht finden bzw. nicht über den dynamischen Loader starten konnte.

Der Workflow verwendet deshalb jetzt:

- einen explizit ermittelten, versionierten Clang-Compiler (`clang++-18` bevorzugt),
- eine über `GITHUB_ENV` fest übergebene `CXX`-Variable,
- statisch eingebettete ASan-/UBSan-Laufzeitbibliotheken (`-static-libsan`),
- einen expliziten Start über `bash --noprofile --norc`,
- ein immer hochgeladenes Diagnoseartefakt mit Toolchain- und Sanitizer-Log.

Das Diagnoseartefakt heißt:

`AstroFocusStudio-3.8.8-Native-Sanitizer-Logs`

Es enthält:

- `toolchain.log`
- `native-sanitizers.log`

Falls ein Testprogramm nicht geladen werden kann, schreibt das Skript zusätzlich
`file`, `ldd` und die Dateirechte des betroffenen Programms in das Log.
