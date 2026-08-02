from pathlib import Path
import sys
sys.dont_write_bytecode = True

root = Path(__file__).resolve().parents[1]
setup_path = root / 'installer' / 'AstroFocusSetup.ps1'
wix_path = root / 'installer' / 'build-wix.ps1'
setup = setup_path.read_text(encoding='utf-8')
wix = wix_path.read_text(encoding='utf-8')


def parameter_header(text: str) -> str:
    marker = 'Set-StrictMode'
    if marker not in text:
        return text
    return text.split(marker, 1)[0]

setup_header = parameter_header(setup)
wix_header = parameter_header(wix)

checks = {
    'setup parameter defaults do not evaluate PSScriptRoot': '$PSScriptRoot' not in setup_header,
    'setup Source parameter has inert empty default': "[string]$Source = ''" in setup_header,
    'setup resolves script directory in executable body': '$ScriptDirectory = $PSScriptRoot' in setup,
    'setup has MyInvocation fallback for script directory': '$MyInvocation.MyCommand.Path' in setup,
    'setup resolves default payload after parameter binding': "$Source = Join-Path -Path $ScriptDirectory -ChildPath 'payload'" in setup,
    'setup uses stable script directory for launcher lookup': "Join-Path $ScriptDirectory 'AstroFocusSetup.exe'" in setup,
    'setup uses stable script directory for development marker': 'Join-Path $ScriptDirectory $DevMarkerName' in setup,
    'WiX parameter defaults do not evaluate PSScriptRoot': '$PSScriptRoot' not in wix_header,
    'WiX Payload and Output defaults are inert': "[string]$Payload=''" in wix_header and "[string]$Output=''" in wix_header,
    'WiX paths are resolved after parameter binding': "Join-Path -Path $ScriptDirectory -ChildPath 'payload'" in wix and "Join-Path -Path $ScriptDirectory -ChildPath 'out'" in wix,
}

for name, ok in checks.items():
    print(f"{name}: {'PASS' if ok else 'FAIL'}")
print(f"SUMMARY {sum(checks.values())}/{len(checks)}")
raise SystemExit(0 if all(checks.values()) else 1)
