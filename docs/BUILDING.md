# Build and test

## Requirements

- LLVM tools: `clang`, `clang-cl`, `lld-link`, `clang++`
- Python 3
- For installer packaging: Windows, PowerShell, .NET 8 and WiX 5

## Cross-build all Windows programs

```bash
./build-windows-x64.sh --clean
```

Output is written to `out/windows-x64/bin`. Source directories remain free of
objects, import libraries and executables.

Useful modes:

```bash
./build-windows-x64.sh --component frontend
./build-windows-x64.sh --test
./build-windows-x64.sh --release
```

## Tests

```bash
python3 -B scripts/run_python_tests.py --phase source
./build-windows-x64.sh --clean
python3 -B scripts/run_python_tests.py --phase post-build
CXX=clang++ ./scripts/Run-NativeTests.sh
```

The Python suite validates repository, build, UI, API, installer and release
contracts. Native tests run with AddressSanitizer and UndefinedBehaviorSanitizer.

## Versioning

Edit only `VERSION`. The build regenerates `common/version.h`, PE version data,
manifest identity, installer versions and release metadata from that value.

## Git for Windows argument handling

The central Bash build deliberately passes LLVM/COFF options with a leading dash
(for example `-nologo` and `-machine:x64`). Do not change these back to the
MSVC-style slash spelling in a Bash script: Git for Windows/MSYS can interpret
`/nologo` as a POSIX path and rewrite it to `C:/Program Files/Git/nologo`.
Windows-only PowerShell or batch scripts may still use slash-style switches.
