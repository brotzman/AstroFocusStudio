# GitHub Actions: lld-link `/version`

Der Windows-Build brach vor dem eigentlichen Kompilieren ab, weil `lld-link.exe /version` verwendet wurde.
`lld-link` interpretiert `/version` nicht als Versionsoption, sondern als zu öffnenden Eingabepfad.

Korrektur:

```powershell
& lld-link.exe --version
```

Damit wird die LLVM-Version ausgegeben, ohne den Linker mit einer vermeintlichen Datei `/version` zu starten.
