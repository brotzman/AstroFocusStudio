# GitHub Actions: Windows-Build Exitcode 1

Der frühere Workflow verwendete beim direkten `wix.exe`-Aufruf die Erweiterungsreferenz
`WixToolset.Bal.wixext`. Für `wix.exe` muss die Bootstrapper-Erweiterung als
`WixToolset.BootstrapperApplications.wixext` geladen werden.

Der Workflow schreibt außerdem den vollständigen Windows-Build in:

```text
artifacts/test-logs/build-package.log
```

Die Protokolle werden mit `if: always()` hochgeladen. Dadurch ist bei einem weiteren
Fehler nicht mehr nur der allgemeine Exitcode sichtbar.
