# AstroFocus Studio 3.8.8

Native Windows-x64-Anwendung für Live-Fokus, statistisch ausgewerteten Autofokus,
Bahtinov-Unterstützung, Fokusautomation und reproduzierbare Simulatorprüfungen.

Die ausführliche deutschsprachige Funktions- und Sicherheitsbeschreibung steht in
[`README_DE.md`](README_DE.md). Bekannte Grenzen sind in
[`KNOWN_LIMITATIONS_3_8_8.txt`](KNOWN_LIMITATIONS_3_8_8.txt) dokumentiert.

## GitHub-Actions-Build

Der Workflow `.github/workflows/windows-build.yml` baut und prüft das Projekt in zwei
voneinander abhängigen Jobs:

1. Native C++-Regressionstests unter Linux mit AddressSanitizer und
   UndefinedBehaviorSanitizer.
2. Vollständiger Windows-x64-Build auf `windows-2022`, Erstellung eines nativen
   WiX-MSI und eines WiX-Burn-Setup-Programms sowie ein realer stiller Installations-,
   Reparatur-, Health-Check- und Deinstallationstest.

Nach einem erfolgreichen Build liegt unter **Actions → Artifacts** das Artefakt
`AstroFocusStudio-3.8.8-Windows-x64`. Es enthält:

- `AstroFocusStudio-3.8.8-Setup.exe`
- `AstroFocusStudio-3.8.8-x64.msi`
- `AstroFocusStudio-3.8.8-Portable-Windows-x64.zip`
- `AstroFocusStudio-3.8.8-Source.zip`
- `SHA256SUMS.txt`
- `BUILD_INFO.txt`

Ein Tag wie `v3.8.8` veröffentlicht dieselben, zuvor geprüften Dateien zusätzlich als
GitHub Release.

## Lokaler Build

### Windows

Voraussetzungen: Windows x64, LLVM/Clang, Python 3.12 oder neuer und .NET SDK 8.

```powershell
.\scripts\Build-GitHubArtifacts.ps1
.\scripts\Test-GitHubInstaller.ps1
```

### Linux

Der Cross-Build der sieben Windows-x64-Programme:

```bash
bash ./build-windows-x64.sh
```

Die nativen Regressionstests:

```bash
bash ./scripts/Run-NativeTests.sh
```

## Ausgelieferte Programme

- `AstroFocusStudio.exe`
- `AstroFocusEngine.exe`
- `AstroFocusCameraHost.exe`
- `AstroFocusFocuserHost.exe`
- `AstroFocusFocuserSetup.exe`
- `AstroFocusUpdater.exe`
- `AstroFocusSetup.exe`

## Entwicklungsstatus

Die von diesem Repository erzeugten Pakete sind nicht Authenticode-signiert. Windows
kann deshalb eine SmartScreen-Warnung anzeigen. Eine Produktionsfreigabe benötigt ein
geschütztes Code-Signing-Verfahren und reale Tests mit den vorgesehenen ASCOM- und
ToupTek-Geräten.

Für dieses Quellpaket wurde keine Lizenzdatei bereitgestellt. Vor einer öffentlichen
Veröffentlichung sollte der Rechteinhaber eine passende `LICENSE` ergänzen.

### GitHub Actions: native sanitizer diagnostics

The native test job selects a versioned Clang compiler explicitly and embeds the
sanitizer runtimes. Its logs are uploaded on every success or failure as
`AstroFocusStudio-3.8.8-Native-Sanitizer-Logs`.
