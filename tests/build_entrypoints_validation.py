from pathlib import Path

root = Path(__file__).resolve().parents[1]
linux = (root / "build-windows-x64.sh").read_text(encoding="utf-8")
windows = (root / "build-all-windows-x64.bat").read_text(encoding="utf-8")
component_wrappers = [
    root / "frontend" / "build-windows-x64.bat",
    root / "backend" / "build-windows-x64.bat",
    root / "focuser_setup" / "build-windows-x64.bat",
    root / "device_host" / "build-windows-x64.bat",
    root / "device_host" / "build-windows-x64.sh",
    root / "tools" / "build-windows-x64.bat",
    root / "tools" / "build-windows-x64.sh",
]
expected_outputs = {
    "AstroFocusStudio.exe", "AstroFocusEngine.exe", "AstroFocusFocuserSetup.exe",
    "AstroFocusCameraHost.exe", "AstroFocusFocuserHost.exe",
    "AstroFocusUpdater.exe", "AstroFocusSetup.exe",
}

checks = {
    "root build has a portable bash shebang": linux.startswith("#!/usr/bin/env bash\n"),
    "root build supports clean, test and release modes": all(token in linux for token in ("--clean", "--test", "--release")),
    "root build supports component selection": "--component" in linux and "COMPONENT=" in linux,
    "all seven output names are owned by the central build": all(name in linux for name in expected_outputs),
    "native outputs are written below out/windows-x64": 'OUT_DIR="${OUT_DIR:-$ROOT/out/windows-x64}"' in linux and 'BIN_DIR="$OUT_DIR/bin"' in linux,
    "generated resources stay outside source directories": 'GEN_DIR="$OUT_DIR/generated"' in linux,
    "all import libraries are regenerated from definition files": "make_import_lib" in linux and ".def" in linux,
    "central version header is generated before compilation": "generate_version.py" in linux and "common/version.h" in linux,
    "Windows resources are generated centrally": "generate_windows_resources.py" in linux and "assets/AstroFocusStudio.ico" in linux,
    "root Windows entry point delegates to central build": "build-windows-x64.sh" in windows and "--clean" in windows,
    "component entry points are thin central-build wrappers": all(
        "build-windows-x64.sh" in path.read_text(encoding="utf-8")
        and "--component" in path.read_text(encoding="utf-8")
        for path in component_wrappers
    ),
    "component wrappers do not duplicate compiler/linker recipes": all(
        "clang-cl" not in path.read_text(encoding="utf-8")
        and "lld-link" not in path.read_text(encoding="utf-8")
        for path in component_wrappers
    ),
    "tool launchers use dedicated wrapper translation units": all(
        (root / "tools" / name).is_file() for name in ("updater_launcher.cpp", "setup_launcher.cpp")
    ),
    "source tree contains no Python cache remnants": not any(root.rglob("*.pyc")) and not any(root.rglob("__pycache__")),
}

for name, ok in checks.items():
    print(f'{name}: {"PASS" if ok else "FAIL"}')
print(f'SUMMARY {sum(checks.values())}/{len(checks)}')
raise SystemExit(0 if all(checks.values()) else 1)
