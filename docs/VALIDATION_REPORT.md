# Validation report — 3 August 2026

## Environment

- Linux x86-64
- Python 3.13.5
- Clang/clang-cl 17.0.0
- LLD 17.0.0

## Completed checks

- Clean LLVM cross-build of all seven Windows-x64 GUI executables with `/W4`,
  `/WX`, optimisation and `/GS` application protection.
- 25 source/repository Python regression programs passed before build.
- 2 post-build Python regression programs passed against generated PE files.
- 27/27 Python regression programs passed as a combined run.
- 275/275 native AddressSanitizer/UndefinedBehaviorSanitizer tests passed:
  12 command-line, 81 frontend, 172 engine/API and 10 continuous-focus tests.
- GitHub Actions/WiX contract suite: 104/104 checks passed.
- WiX XML and GitHub workflow YAML parsed successfully.
- Bash syntax, Python syntax and `git diff --check` passed.
- All generated programs were identified as PE32+ x86-64 executables.
- PE resources contain the central 3.9.0 product version, icon, `asInvoker`
  privilege declaration, long-path support and automatic GDI DPI scaling.
- Source component directories contain no committed `.exe`, `.obj`, `.lib`,
  `.res` or duplicate icon files.

## Behaviour added

- Basis/Experte UI selector with a compatibility-safe expert default.
- Consolidated camera/focuser/focus/FWHM status rail.
- Single version source (`VERSION`) and generated version header/resources.
- Single central loopback endpoint definition.
- Out-of-tree deterministic build under `out/windows-x64`.
- Stable test names and explicit source/post-build phases.
- Permanent architecture, build, API, security and first-run documentation.

## Checks that require a real Windows system

This environment has no Windows runtime, PowerShell, Wine, ASCOM platform,
ToupTek SDK or physical astronomy hardware. Therefore the following cannot be
executed here and remain mandatory before unattended release:

- Visible Windows 10/11 GUI inspection at common display scales.
- Real ASCOM chooser/setup dialogs and driver timeout behaviour.
- Real camera live frames and focuser movement/halt/end-stop verification.
- WiX MSI/Burn installation, repair, UAC, desktop shortcut and rollback.
- Standby/resume and USB-disconnect tests.

The repository's Windows GitHub Actions workflow and static contracts cover the
packaging paths, but they do not replace physical target-system testing.

## Deliberately deferred architecture projects

A complete headless-engine conversion, replacement of frontend HTTP IPC with
Named Pipes, direct ASCOM filter-wheel control and guide/OAG/ONAG acquisition
were not silently added. Each changes compatibility or hardware safety and needs
its own staged implementation with real Windows devices. The current code now
centralises the endpoint and documents these boundaries so those projects can be
implemented without mixing them into repository cleanup.

## DPI decision

The manifest intentionally uses Windows automatic GDI scaling rather than
claiming PerMonitorV2 awareness. The current UI still contains fixed-pixel layout
logic; declaring PerMonitorV2 without scaling every coordinate and font would
make the interface smaller or clipped. True per-monitor scaling should be a
separate visual regression project on Windows.
