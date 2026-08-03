# Changelog

The authoritative product version is stored in `VERSION`. Detailed historical
notes for the current release are in `RELEASE_NOTES.txt`.

## Corrective maintenance

- Prevent Git for Windows/MSYS from rewriting LLVM COFF switches such as `/nologo` into paths like `C:/Program Files/Git/nologo`; the Bash build now uses LLVM-compatible dash-prefixed options.
- Add a regression test that rejects MSVC-style slash switches passed from Bash to `clang-cl` or `lld-link`.
- Convert every source, object, resource, import-library and output path passed to native Windows LLVM tools with `cygpath -am` when running under Git Bash/MSYS; embedded options such as `-Fo:` no longer contain unconverted `/d/a/...` paths.
- Extend the Git Bash regression test with a simulated MINGW toolchain run that records and verifies every native-tool argument.
- Automatically synchronise a successfully calibrated backlash value into the visible autofocus settings while preserving unrelated unsaved edits.
- Store the calibrated value in the active runtime autofocus state and focus model.
- Widen and relabel the Tests-page button to “Simulation übernehmen” so the full caption remains visible.

## Repository optimisation pass

- Centralised product version, Windows metadata, icon and application manifest.
- Moved all native outputs to `out/windows-x64` and removed committed binaries.
- Consolidated component entry points into one deterministic build script.
- Added stable, version-independent test names and deterministic test discovery.
- Added Basis/Experte view selection and a consolidated operational status rail.
- Centralised the loopback endpoint definition and documented API boundaries.
- Added architecture, build, first-run, contribution and security documentation.
