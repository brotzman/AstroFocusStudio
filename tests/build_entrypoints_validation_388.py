from pathlib import Path

root = Path(__file__).resolve().parents[1]
linux = (root / "build-windows-x64.sh").read_text(encoding="utf-8")
windows = (root / "build-all-windows-x64.bat").read_text(encoding="utf-8")

component_dirs = ("frontend", "backend", "focuser_setup", "device_host", "tools")
expected_outputs = {
    "AstroFocusStudio.exe", "AstroFocusEngine.exe", "AstroFocusFocuserSetup.exe",
    "AstroFocusCameraHost.exe", "AstroFocusFocuserHost.exe",
    "AstroFocusUpdater.exe", "AstroFocusSetup.exe",
}

checks = {
    "root Linux build script has a portable bash shebang":
        (root / "build-windows-x64.sh").read_text(encoding="utf-8").startswith("#!/usr/bin/env bash\n"),
    "nested Linux build scripts have portable bash shebangs": all(
        (root / directory / "build-windows-x64.sh").read_text(encoding="utf-8").startswith("#!/usr/bin/env bash\n")
        for directory in ("device_host", "tools")
    ),
    "Linux aggregate build includes device hosts": '"$ROOT/device_host/build-windows-x64.sh"' in linux,
    "Linux aggregate build includes setup and updater": '"$ROOT/tools/build-windows-x64.sh"' in linux,
    "Windows aggregate build invokes all component builders": all(
        f"call :build {directory}" in windows for directory in component_dirs
    ),
    "Windows aggregate build does not claim completion after only three components":
        windows.index("call :build tools") < windows.index("wurde vollständig erstellt"),
    "all seven output names are represented by component build scripts": expected_outputs == {
        name
        for script in root.glob("*/build-windows-x64.*")
        for name in expected_outputs
        if name in script.read_text(encoding="utf-8", errors="ignore")
    },
    "source tree contains no Python cache remnants": not any(root.rglob("*.pyc")) and not any(root.rglob("__pycache__")),
}

for name, ok in checks.items():
    print(f'{name}: {"PASS" if ok else "FAIL"}')
print(f'SUMMARY {sum(checks.values())}/{len(checks)}')
raise SystemExit(0 if all(checks.values()) else 1)
