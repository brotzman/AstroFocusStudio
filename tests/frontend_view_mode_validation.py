from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
front = (ROOT / "frontend" / "frontend.cpp").read_text(encoding="utf-8")
checks = []

def check(name: str, ok: bool) -> None:
    checks.append(ok)
    print(f"{name}: {'PASS' if ok else 'FAIL'}")

check("view selector has a dedicated command id", "#define ID_VIEW_MODE 1136" in front)
check("view selector offers Basis and Experte", 'ComboAdd(hViewMode,L"Basis")' in front and 'ComboAdd(hViewMode,L"Experte")' in front)
check("expert view remains the compatibility default", "g_expertMode=TRUE" in front and "ComboSelect(hViewMode,g_expertMode?1:0)" in front)
check("basic view exposes exactly four primary tabs", "int visibleTabs=g_expertMode?8:4" in front)
check("basic view safely returns from hidden expert pages", front.count("!g_expertMode&&g_activeTab>=4") >= 2)
check("hidden tabs are removed from keyboard and mouse access", "ShowCtl(hTabs[i],visible)" in front)
check("view changes relayout the complete client area", "expert view enabled" in front and "Layout(g_layoutClientWidth,g_layoutClientHeight)" in front)
check("status rail combines both device states", 'L"%s Kamera   %s Fokussierer' in front)
check("status rail includes focus position and FWHM", 'L"Fokus %d"' in front and 'FWHM %s' in front)
check("status formatting uses a bounded local buffer", "wchar_t status[760]" in front)

print(f"SUMMARY {sum(checks)}/{len(checks)}")
raise SystemExit(0 if all(checks) else 1)
