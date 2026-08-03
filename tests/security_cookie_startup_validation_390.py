from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
failures = 0
checks = 0

def check(condition: bool, message: str) -> None:
    global failures, checks
    checks += 1
    if condition:
        print(f"{message}: PASS")
    else:
        failures += 1
        print(f"{message}: FAIL")

entry_path = ROOT / "common" / "security_entry.cpp"
entry = entry_path.read_text(encoding="utf-8") if entry_path.exists() else ""
program_sources = [
    ROOT / "frontend" / "frontend.cpp",
    ROOT / "backend" / "backend.cpp",
    ROOT / "focuser_setup" / "focuser_setup.cpp",
    ROOT / "device_host" / "device_host.cpp",
    ROOT / "tools" / "tool_launcher.cpp",
]
build_scripts = [
    ROOT / "build-windows-x64.sh",
    ROOT / "frontend" / "build-windows-x64.bat",
    ROOT / "backend" / "build-windows-x64.bat",
    ROOT / "focuser_setup" / "build-windows-x64.bat",
    ROOT / "device_host" / "build-windows-x64.bat",
    ROOT / "device_host" / "build-windows-x64.sh",
    ROOT / "tools" / "build-windows-x64.bat",
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
    check("extern \"C\" void AstroFocusApplicationMain()" in text, f"{rel} exports the shared application-main symbol")
    check("WinMainCRTStartup" not in text, f"{rel} no longer defines the process entry")
    check("__security_init_cookie();" not in text, f"{rel} no longer changes the cookie inside /GS-protected code")

for script in build_scripts:
    text = script.read_text(encoding="utf-8")
    rel = script.relative_to(ROOT).as_posix()
    check("security_entry.cpp" in text, f"{rel} compiles the dedicated security entry")
    check("security_entry.obj" in text, f"{rel} links the dedicated security entry")
    compact = " ".join(text.replace("\\", "/").split())
    entry_compile = any(
        "/GS-" in segment and "security_entry.cpp" in segment
        for segment in compact.split("||")
    ) if script.suffix.lower() == ".bat" else "/GS- /c" in compact and "security_entry.cpp" in compact
    check(entry_compile, f"{rel} compiles the entry with /GS disabled")
    check("/GS /DUNICODE" in compact, f"{rel} keeps application code protected with /GS")

all_cpp = list(ROOT.rglob("*.cpp"))
entry_definitions = []
for source in all_cpp:
    try:
        text = source.read_text(encoding="utf-8")
    except UnicodeDecodeError:
        continue
    if "void WinMainCRTStartup()" in text:
        entry_definitions.append(source.relative_to(ROOT).as_posix())
check(entry_definitions == ["common/security_entry.cpp"], "only the dedicated /GS-disabled source defines WinMainCRTStartup")

print(f"SUMMARY {checks - failures}/{checks}")
sys.exit(1 if failures else 0)
