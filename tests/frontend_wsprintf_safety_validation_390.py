from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / 'frontend' / 'frontend.cpp').read_text(encoding='utf-8')

checks = []
def check(name: str, condition: bool) -> None:
    checks.append((name, bool(condition)))
    print(f"{name}: {'PASS' if condition else 'FAIL'}")

check('USER32 wsprintf formats contain no unsupported explicit plus flag', '%+' not in SOURCE)
check('signed integer formatter exists', 'static void FormatSignedInt(int value,wchar_t* out,int cap)' in SOURCE)
check('signed integer formatter writes the plus sign explicitly', 'if(value>0)AppendWBounded(out,cap,L"+")' in SOURCE)
check('bounded wide-string append helper exists', 'static void AppendWBounded(wchar_t* out,int cap,LPCWSTR text)' in SOURCE)
check('continuous-focus correction uses the bounded signed formatter', 'FormatSignedInt(g_state.continuousFocusLastCorrection,lastCorrection,32)' in SOURCE)
check('continuous-focus status avoids legacy USER32 formatting', 'cfInfo[0]=0;AppendWBounded(cfInfo,1800' in SOURCE and 'wsprintfW(cfInfo' not in SOURCE)
check('session position delta uses the bounded signed formatter', 'FormatSignedInt(g_state.sessionLastPosition-g_state.sessionStartPosition,signedShift,32)' in SOURCE)
check('UI update records a dedicated continuous-focus phase', 'SetFrontendPhase("UI state update: continuous focus")' in SOURCE)
check('UI update records automation and profile phases', 'SetFrontendPhase("UI state update: automation")' in SOURCE and 'SetFrontendPhase("UI state update: profile controls")' in SOURCE)

# wsprintfW is an intentionally small legacy formatter. Keep the format set
# conservative and reject flags/modifiers that are not supported by USER32.
formats = re.findall(r'wsprintfW\s*\([^,]+,\s*L"((?:\\.|[^"\\])*)"', SOURCE)
unsafe = []
for fmt in formats:
    i = 0
    while i < len(fmt):
        if fmt[i] != '%':
            i += 1
            continue
        if i + 1 < len(fmt) and fmt[i + 1] == '%':
            i += 2
            continue
        j = i + 1
        while j < len(fmt) and fmt[j] in '-#0':
            j += 1
        while j < len(fmt) and fmt[j].isdigit():
            j += 1
        if j < len(fmt) and fmt[j] == '.':
            j += 1
            while j < len(fmt) and fmt[j].isdigit():
                j += 1
        if j >= len(fmt) or fmt[j] not in 'cCdiouxXsS':
            unsafe.append((fmt, fmt[i:min(len(fmt), j + 1)]))
            break
        i = j + 1
check('all USER32 wsprintf conversions stay inside the supported subset', not unsafe)
if unsafe:
    for fmt, spec in unsafe:
        print(f'UNSAFE: {spec} in {fmt}')

passed = sum(ok for _, ok in checks)
print(f'SUMMARY {passed}/{len(checks)}')
raise SystemExit(0 if passed == len(checks) else 1)
