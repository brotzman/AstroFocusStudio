from pathlib import Path
import subprocess
import sys
sys.dont_write_bytecode = True

root = Path(__file__).resolve().parents[1]
launcher = (root / "tools" / "tool_launcher.cpp").read_text(encoding="utf-8")
setup = (root / "installer" / "AstroFocusSetup.ps1").read_text(encoding="utf-8")
cmd = (root / "installer" / "Install-Development.cmd").read_text(encoding="utf-8")
readme = (root / "installer" / "README_INSTALLER_DE.md").read_text(encoding="utf-8")
exe = root / "out" / "windows-x64" / "bin" / "AstroFocusSetup.exe"

checks = {
    "launcher resolves Windows PowerShell from system directory": "GetSystemDirectoryW" in launcher and "\\\\WindowsPowerShell\\\\v1.0\\\\powershell.exe" in launcher,
    "launcher bypasses download policy for fixed sibling script": "-ExecutionPolicy Bypass" in launcher and "ASTROFOCUS_SCRIPT_NAME" in launcher,
    "launcher reports native bootstrap failures": "MessageBoxW" in launcher and "ShowBootstrapError" in launcher,
    "launcher verifies script and PowerShell existence": launcher.count("IsRegularFile(") >= 3,
    "development setup auto-detects explicit marker": "ASTROFOCUS_AUTO_DEV_SWITCH" in launcher and "UNSIGNED_DEVELOPMENT_BUILD.txt" in launcher,
    "elevated child is waited for and result is surfaced": "-Verb RunAs -Wait -PassThru" in setup and "Show-InstallerMessage (Get-ModeSuccessMessage)" in setup,
    "installer shows detailed visible errors": "Diagnoseprotokoll:" in setup and "-ErrorIcon" in setup,
    "download zone identifiers are cleared only in development mode": "Clear-DevelopmentZoneIdentifiers" in setup and "Test-DevelopmentModeAllowed" in setup and "Test-PayloadDevelopmentMarker" in setup,
    "top-level launch and elevation errors are caught": "try {\n    Start-RelocatedDestructiveMode\n    Wait-ForPreviousInstance\n    Request-Elevation" in setup,
    "development command preserves failure output": "pause" in cmd.lower() and "Installer.log" in cmd,
    "documentation requires full extraction and identifies log": "vollständig" in readme and "Installer.log" in readme,
    "rebuilt setup launcher exists in the out-of-tree bin directory": exe.is_file(),
}

if exe.is_file():
    result = subprocess.run(["objdump", "-p", str(exe)], capture_output=True, text=True, check=False)
    imports = result.stdout
    checks["binary imports native error dialog and fixed-path APIs"] = all(name in imports for name in ("MessageBoxW", "GetSystemDirectoryW", "GetFileAttributesW"))
    strings = subprocess.run(["strings", "-el", str(exe)], capture_output=True, text=True, check=False).stdout
    checks["binary contains bypass policy and installer log hint"] = "ExecutionPolicy Bypass" in strings and "Installer.log" in strings

for name, ok in checks.items():
    print(f"{name}: {'PASS' if ok else 'FAIL'}")
print(f"SUMMARY {sum(checks.values())}/{len(checks)}")
raise SystemExit(0 if all(checks.values()) else 1)
