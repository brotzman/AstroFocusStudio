# Contributing

1. Create a focused branch and keep generated files out of source directories.
2. Change the product version only in `VERSION`; regenerate `common/version.h`
   with `python -B tools/generate_version.py --version-file VERSION --header common/version.h`.
3. Build with `./build-windows-x64.sh --clean --test`.
4. Keep hardware actions fail-closed and preserve the exposure/movement interlocks.
5. Add or update behaviour-based regression tests for every correction.
6. Do not commit `.exe`, `.obj`, `.lib`, `.res`, installer payloads, logs, or keys.

Pull requests should state the affected component, safety impact, test evidence,
and whether real ASCOM/ToupTek hardware was used.
