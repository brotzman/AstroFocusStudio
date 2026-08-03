# AstroFocus Studio 3.9.0

Native Windows-x64-Anwendung für Live-Fokus, statistisch ausgewerteten Autofokus,
Bahtinov-Unterstützung, Fokusautomation und reproduzierbare Simulatorprüfungen.

Die ausführliche deutschsprachige Funktions- und Sicherheitsbeschreibung steht in
[`README_DE.md`](README_DE.md). Bekannte Grenzen sind in
[`KNOWN_LIMITATIONS_3_9_0.txt`](KNOWN_LIMITATIONS_3_9_0.txt) dokumentiert.

## GitHub-Actions-Build

Der Workflow `.github/workflows/windows-build.yml` baut und prüft das Projekt in zwei
voneinander abhängigen Jobs:

1. Native C++-Regressionstests unter Linux mit AddressSanitizer und
   UndefinedBehaviorSanitizer.
2. Vollständiger Windows-x64-Build auf `windows-2022`, Erstellung eines nativen
   WiX-MSI und eines WiX-Burn-Setup-Programms sowie ein realer stiller Installations-,
   Reparatur-, Health-Check- und Deinstallationstest.

Nach einem erfolgreichen Build liegt unter **Actions → Artifacts** das Artefakt
`AstroFocusStudio-3.9.0-Windows-x64`. Es enthält:

- `AstroFocusStudio-3.9.0-Setup.exe`
- `AstroFocusStudio-3.9.0-x64.msi`
- `AstroFocusStudio-3.9.0-Portable-Windows-x64.zip`
- `AstroFocusStudio-3.9.0-Source.zip`
- `SHA256SUMS.txt`
- `BUILD_INFO.txt`

Ein Tag wie `v3.9.0` veröffentlicht dieselben, zuvor geprüften Dateien zusätzlich als
GitHub Release. Alternativ kann der Workflow manuell mit `publish_release: true` und
`release_tag: v3.9.0` gestartet werden; der Tag wird dann nach allen erfolgreichen
Tests am geprüften Commit erstellt, sofern er noch nicht existiert.

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
`AstroFocusStudio-3.9.0-Native-Sanitizer-Logs`.

## CI repository integrity

- The Windows workflow validates all required `scripts/` entry points and invokes the artifact build from the absolute `GITHUB_WORKSPACE` path.

## CI health checks and failed-run cleanup

The Windows installer smoke tests execute the camera host, focuser host, and
engine as three independent health checks. Burn and raw MSI transactions run in two
separate jobs on fresh Windows runners, so Burn registration, pending restart state,
or Windows Installer transaction state cannot leak into the raw MSI test. See
`docs/GITHUB_ACTIONS_MSI_RUNNER_ISOLATION_FIX_DE.md` for the detailed German note.

### Standard main-window behaviour

- When minimized, AstroFocus Studio remains visible as a normal Windows taskbar button.
- The main window is no longer hidden or moved to the notification area and can be restored or maximized normally from the taskbar.


### Desktop shortcut

The per-machine WiX installer creates **AstroFocus Studio.lnk** on the public Windows desktop. Both the Burn and raw-MSI smoke tests verify its target and working directory, repair preserves it, and uninstall removes it.

## Continuous focus tracking

The new **Nachführung** expert page provides predictive, image-based, and hybrid focus tracking. It reuses normal AstroFocus live frames, applies bounded micro-corrections only after an exposure has completed, waits for settling, and accepts a correction only after improved verification frames. Failed probes return to the original position and can optionally fall back to a complete autofocus run.

The responsive page keeps labels, numeric fields, status text, controls, and its position/target chart inside the supported minimum window geometry. Long diagnostics scroll and the chart retains a minimum height.

This 3.9.0 implementation does not yet consume a separate guide/OAG/ONAG stream and never moves the focuser during an active main exposure. See [`docs/CONTINUOUS_FOCUS_DE.md`](docs/CONTINUOUS_FOCUS_DE.md) for the detailed German specification and limitations.
