from pathlib import Path
import tempfile
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
generator = (ROOT / "tools" / "generate_windows_resources.py").read_text(encoding="utf-8")
build = (ROOT / "build-windows-x64.sh").read_text(encoding="utf-8")
checks = []

def check(name: str, ok: bool) -> None:
    checks.append(ok)
    print(f"{name}: {'PASS' if ok else 'FAIL'}")

check("manifest runs without elevation", 'requestedExecutionLevel level="asInvoker"' in generator)
check("manifest enables automatic GDI DPI scaling", '<gdiScaling xmlns="http://schemas.microsoft.com/SMI/2017/WindowsSettings">true</gdiScaling>' in generator)
check("manifest does not falsely claim PerMonitorV2 layout support", "PerMonitorV2" not in generator)
check("manifest enables long paths", '<longPathAware xmlns="http://schemas.microsoft.com/SMI/2016/WindowsSettings">true</longPathAware>' in generator)
check("manifest declares supported Windows versions", generator.count("<supportedOS Id=") >= 5)
check("PE metadata uses central semantic version", "read_version(version_path)" in generator and 'string_block("ProductVersion", text)' in generator)
check("all applications receive generated resources", build.count("make_resources") >= 8 and '"$res"' in build)
central_icon = ROOT / "assets" / "AstroFocusStudio.ico"
duplicate_icons = [ROOT / directory / "AstroFocusStudio.ico" for directory in ("frontend", "backend", "focuser_setup")]
central_icon_ok = central_icon.is_file() and 'assets/AstroFocusStudio.ico' in build and not any(path.is_file() for path in duplicate_icons)
check("one central icon is used", central_icon_ok)
if not central_icon_ok:
    print(f"  central icon: {central_icon} ({'present' if central_icon.is_file() else 'missing'})")
    for path in duplicate_icons:
        if path.is_file():
            print(f"  duplicate icon: {path}")

with tempfile.TemporaryDirectory() as temporary:
    target = Path(temporary) / "test.res"
    result = subprocess.run([
        sys.executable, "-B", str(ROOT / "tools" / "generate_windows_resources.py"),
        "--icon", str(ROOT / "assets" / "AstroFocusStudio.ico"),
        "--version-file", str(ROOT / "VERSION"), "--output", str(target),
        "--exe", "AstroFocusStudio.exe", "--description", "Resource validation",
    ], capture_output=True, text=True)
    check("resource generation succeeds from a clean directory", result.returncode == 0 and target.is_file() and target.stat().st_size > 1024)
    if target.is_file():
        data = target.read_bytes()
        check("generated resource embeds application manifest XML", b"requestedExecutionLevel" in data and b"gdiScaling" in data)

print(f"SUMMARY {sum(checks)}/{len(checks)}")
raise SystemExit(0 if all(checks) else 1)
