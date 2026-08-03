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
    "device-host build deletes optional linker stubs only when present":
        'if exist "%%D_stub.dll" del /q "%%D_stub.dll" >nul 2>&1' in
        (root / "device_host" / "build-windows-x64.bat").read_text(encoding="utf-8"),
    "tool build deletes optional linker stubs only when present": all(
        f'if exist "{name}_stub.dll" del /q "{name}_stub.dll" >nul 2>&1' in
        (root / "tools" / "build-windows-x64.bat").read_text(encoding="utf-8")
        for name in ("kernel32", "user32")
    ),
    "batch builds contain no unconditional deletion of optional stub DLLs": all(
        not line.lstrip().lower().startswith("del /q ")
        for script in (root / "device_host" / "build-windows-x64.bat", root / "tools" / "build-windows-x64.bat")
        for line in script.read_text(encoding="utf-8").splitlines()
    ),
    "tool launchers use dedicated wrapper translation units": all(
        (root / "tools" / name).is_file() for name in ("updater_launcher.cpp", "setup_launcher.cpp")
    ),
    "updater wrapper provides fixed launcher metadata": all(
        token in (root / "tools" / "updater_launcher.cpp").read_text(encoding="utf-8")
        for token in (
            '#define ASTROFOCUS_SCRIPT_NAME L"AstroFocusUpdater.ps1"',
            '#define ASTROFOCUS_TOOL_TITLE L"AstroFocus Studio Updater"',
            '#include "tool_launcher.cpp"',
        )
    ),
    "setup wrapper provides fixed launcher metadata and development switch": all(
        token in (root / "tools" / "setup_launcher.cpp").read_text(encoding="utf-8")
        for token in (
            '#define ASTROFOCUS_SCRIPT_NAME L"AstroFocusSetup.ps1"',
            '#define ASTROFOCUS_TOOL_TITLE L"AstroFocus Studio Setup"',
            '#define ASTROFOCUS_AUTO_DEV_SWITCH',
            '#include "tool_launcher.cpp"',
        )
    ),
    "Windows tool build compiles one wrapper source per Fo output": all(
        token in (root / "tools" / "build-windows-x64.bat").read_text(encoding="utf-8")
        for token in (
            '/c updater_launcher.cpp /Fo:updater_launcher.obj',
            '/c setup_launcher.cpp /Fo:setup_launcher.obj',
        )
    ),
    "tool build scripts contain no space-bearing launcher macros on command line": all(
        '/DASTROFOCUS_TOOL_TITLE=' not in (root / "tools" / script).read_text(encoding="utf-8")
        for script in ("build-windows-x64.bat", "build-windows-x64.sh")
    ),
    "source tree contains no Python cache remnants": not any(root.rglob("*.pyc")) and not any(root.rglob("__pycache__")),
}

for name, ok in checks.items():
    print(f'{name}: {"PASS" if ok else "FAIL"}')
print(f'SUMMARY {sum(checks.values())}/{len(checks)}')
raise SystemExit(0 if all(checks.values()) else 1)
