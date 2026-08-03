#!/usr/bin/env python3
"""Layout contracts preventing clipping on the expert continuous-focus page."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
FRONTEND = (ROOT / "frontend" / "frontend.cpp").read_text(encoding="utf-8")

checks: list[tuple[str, bool]] = []

def check(name: str, condition: bool) -> None:
    checks.append((name, condition))
    print(f"{name}: {'PASS' if condition else 'FAIL'}")

check("navigation defines exactly eight tab labels", 'const wchar_t* tabs[8]' in FRONTEND)
check("navigation defines eight minimum widths", re.search(r"int tabMin\[8\]=\{[^}]+\}", FRONTEND) is not None)
check("tracking page has a dedicated sixth tab", 'L"Nachführung"' in FRONTEND and "g_activeTab==5" in FRONTEND)
check("analysis and tests were shifted without overlap", "g_activeTab==6" in FRONTEND and "g_activeTab==7" in FRONTEND)

layout = re.search(
    r"// Continuous-focus page -+\n(?P<body>.*?)\n\s*int simLabelW=",
    FRONTEND,
    re.DOTALL,
)
body = layout.group("body") if layout else ""
check("tracking layout is derived from the current page width", "pw" in body and "g_page.right" in body)
check("tracking top rail has an explicit inter-column gap", "cfGap=18" in body)
check("configuration area retains a minimum usable width", "cfMinConfigW=430" in body)
check("status column collapses instead of forcing horizontal overflow", "if(cfInfoW<270){cfInfoW=0;cfGap=0;}" in body)
check("configuration fields use two calculated equal columns", "cfLeftW=(cfConfigW-18)/2" in body and "cfRightX=px+cfLeftW+18" in body)
check("label and edit widths exactly fit one configuration column", "cfLabelW=cfLeftW-cfEditW-8" in body)
check("all six labels use the calculated label width", sum(f"hCfLabels[{i}]" in body for i in range(6)) == 6)
check("three action buttons share the available width", "cfButtonW=(cfConfigW-2*cfButtonGap)/3" in body)
check("last button consumes the remainder to avoid rounding overflow", "cfConfigW-2*(cfButtonW+cfButtonGap)" in body)
check("status text and scope note are vertically separated", "cfTopH-70" in body and "cfTopH-64" in body)
check("scope note has a reserved readable height", "cfInfoW,64" in body)
check("chart is placed below the complete top rail", "cfChartTop=py+cfTopH+12" in body)
check("chart keeps a minimum 100 pixel height", "g_cfChart.bottom-g_cfChart.top<100" in body and "g_cfChart.bottom-100" in body)
check("chart right edge stays inside the page padding", "g_page.right-18" in body)
check("status control scrolls rather than clipping long diagnostics", "ES_MULTILINE|ES_AUTOVSCROLL|ES_READONLY|WS_VSCROLL" in FRONTEND)
check("status control has internal text margins", "EM_SETMARGINS" in FRONTEND and "MAKELPARAM(8,8)" in FRONTEND)
check("long scope explanation wraps instead of using a single-line style", "hCfNote=Add" in FRONTEND and "SS_LEFT" in FRONTEND)
check("long button captions are explicitly multiline", all(caption in FRONTEND for caption in ("Einstellungen speichern", "Referenz neu aufbauen", "Nachführung freigeben")) and "BS_MULTILINE" in FRONTEND)

# Arithmetic check at the supported minimum client geometry used by the app.
# Layout constants: left 280, right 270, outer gaps/padding from Layout().
# Parse the actual page calculations and evaluate the resulting continuous page widths.
page_match = re.search(r"int leftW=(\d+),rightW=(\d+),gap=(\d+),margin=(\d+)", FRONTEND)
if page_match:
    left_w, right_w, gap, margin = map(int, page_match.groups())
else:
    left_w, right_w, gap, margin = 280, 270, 14, 18
minimum_client_width = 1490
center_width = minimum_client_width - margin * 2 - left_w - right_w - gap * 2
# g_page has 18 px inner padding on both sides.
pw = center_width - 36
cf_gap = 18
cf_info = max(300, min(390, pw * 36 // 100))
if pw - cf_info - cf_gap < 430:
    cf_info = pw - cf_gap - 430
if cf_info < 270:
    cf_info = 0
    cf_gap = 0
cf_config = pw - cf_info - cf_gap
cf_left = (cf_config - 18) // 2
cf_edit = max(78, min(98, cf_left * 36 // 100))
cf_label = cf_left - cf_edit - 8
check("minimum-width arithmetic leaves at least 430 px for controls", cf_config >= 430)
check("minimum-width arithmetic leaves readable labels", cf_label >= 90)
check("minimum-width arithmetic keeps edit controls within their column", cf_label + 8 + cf_edit <= cf_left)
check("minimum-width arithmetic never exceeds the page width", cf_config + cf_gap + cf_info == pw)

failed = [name for name, ok in checks if not ok]
print(f"SUMMARY {len(checks) - len(failed)}/{len(checks)}")
if failed:
    raise SystemExit(1)
