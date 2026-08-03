from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
failures = 0
checks = 0

def check(condition: bool, message: str) -> None:
    global failures, checks
    checks += 1
    print(f"{message}: {'PASS' if condition else 'FAIL'}")
    failures += 0 if condition else 1

entry_path = ROOT / "common" / "security_entry.cpp"
entry = entry_path.read_text(encoding="utf-8") if entry_path.exists() else ""
program_sources = [
    ROOT / "frontend" / "frontend.cpp", ROOT / "backend" / "backend.cpp",
    ROOT / "focuser_setup" / "focuser_setup.cpp", ROOT / "device_host" / "device_host.cpp",
    ROOT / "tools" / "tool_launcher.cpp",
]
central_build = (ROOT / "build-windows-x64.sh").read_text(encoding="utf-8")
wrappers = [
    ROOT / "frontend" / "build-windows-x64.bat", ROOT / "backend" / "build-windows-x64.bat",
    ROOT / "focuser_setup" / "build-windows-x64.bat", ROOT / "device_host" / "build-windows-x64.bat",
    ROOT / "device_host" / "build-windows-x64.sh", ROOT / "tools" / "build-windows-x64.bat",
    ROOT / "tools" / "build-windows-x64.sh",
]

check(entry_path.is_file(), "dedicated no-CRT security entry source exists")
check("void WinMainCRTStartup()" in entry, "dedicated entry defines WinMainCRTStartup")
check("__security_init_cookie();" in entry, "dedicated entry initializes the security cookie")
check("AstroFocusApplicationMain();" in entry, "dedicated entry calls the protected application main")
check(entry.find("__security_init_cookie();") < entry.find("AstroFocusApplicationMain();"), "cookie initialization precedes protected application code")

for source in program_sources:
    text = source.read_text(encoding="utf-8")
    rel = source.relative_to(ROOT).as_posix()
    check('extern "C" void AstroFocusApplicationMain()' in text, f"{rel} exports the shared application-main symbol")
    check("WinMainCRTStartup" not in text, f"{rel} no longer defines the process entry")
    check("__security_init_cookie();" not in text, f"{rel} no longer changes the cookie inside /GS-protected code")

compact = " ".join(central_build.replace("\\", "/").split())
check("security_entry.cpp" in central_build, "central build compiles the dedicated security entry")
check("security_entry.obj" in central_build, "central build links the dedicated security entry")
check("/GS- /c" in compact and "security_entry.cpp" in compact, "central build compiles the entry with /GS disabled")
check("/GS /DUNICODE" in compact, "central build keeps application code protected with /GS")
for wrapper in wrappers:
    text = wrapper.read_text(encoding="utf-8")
    rel = wrapper.relative_to(ROOT).as_posix()
    check("build-windows-x64.sh" in text and "--component" in text, f"{rel} delegates to the secured central build")
    check("security_entry.cpp" not in text, f"{rel} does not duplicate security compile logic")

entry_definitions = []
for source in ROOT.rglob("*.cpp"):
    try: text = source.read_text(encoding="utf-8")
    except UnicodeDecodeError: continue
    if "void WinMainCRTStartup()" in text:
        entry_definitions.append(source.relative_to(ROOT).as_posix())
check(entry_definitions == ["common/security_entry.cpp"], "only the dedicated /GS-disabled source defines WinMainCRTStartup")

print(f"SUMMARY {checks - failures}/{checks}")
sys.exit(1 if failures else 0)
