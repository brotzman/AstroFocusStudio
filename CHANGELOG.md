# Changelog

The authoritative product version is stored in `VERSION`. Detailed historical
notes for the current release are in `RELEASE_NOTES.txt`.

## Corrective maintenance

- Accept any absolute native Windows drive path such as `C:/...` or `D:/...` in the Git Bash/MSYS argument regression test; raw MSYS paths such as `/d/a/...` remain rejected.
- Resolve Git for Windows Bash explicitly in the MSYS argument regression test; the Windows WSL launcher (`System32\bash.exe`) and WindowsApps aliases are rejected before execution.
- Make version consistency checks independent of Windows CRLF checkout conversion and Windows wildcard behaviour; generated headers are compared by text and versioned test filenames are detected with an explicit semantic-version pattern.
- Pin C/C++ header files to LF in `.gitattributes` so generated version headers remain byte-stable across platforms.
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
