from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
FRONTEND = (ROOT / "frontend" / "frontend.cpp").read_text(encoding="utf-8")

checks: list[tuple[str, bool]] = []

def check(name: str, condition: bool) -> None:
    checks.append((name, condition))
    print(f"{name}: {'PASS' if condition else 'FAIL'}")

create_match = re.search(
    r"g_main=CreateWindowExW\(0,L\"AstroFocusStudioWindow\",L\"AstroFocus Studio 3\.8\.8\",(?P<style>[^;]+);",
    FRONTEND,
)
style = create_match.group("style") if create_match else ""

check("main window uses a normal zero extended style", bool(create_match))
check("main window has the standard overlapped caption", "WS_OVERLAPPED" in style and "WS_CAPTION" in style)
check("main window has the standard system menu", "WS_SYSMENU" in style)
check("main window has minimize and maximize buttons", "WS_MINIMIZEBOX" in style and "WS_MAXIMIZEBOX" in style)
check("main window has a resizable frame", "WS_THICKFRAME" in style)
check("main window has no tool-window style", "WS_EX_TOOLWINDOW" not in FRONTEND)
check("main window is unowned and therefore eligible for the taskbar", ",1720,1020,0,0,g_inst,0)" in FRONTEND)

size_match = re.search(
    r"if\(m==WM_SIZE\)\{(?P<body>.*?)if\(m==WM_MOUSEMOVE\)",
    FRONTEND,
    re.DOTALL,
)
size_body = size_match.group("body") if size_match else ""
check("minimized WM_SIZE path remains visible to the Windows taskbar", "if(w==SIZE_MINIMIZED)return 0;" in size_body)
check("minimize path never hides the main window", "SW_HIDE" not in size_body and "ShowWindow" not in size_body)
check("minimize path does not create a notification-area icon", "Tray" not in size_body and "TRAY" not in size_body)

tray_tokens = (
    "NOTIFYICONDATA",
    "Shell_NotifyIcon",
    "WM_TRAYICON",
    "AddTrayIcon",
    "RemoveTrayIcon",
    "NIM_ADD",
    "NIM_DELETE",
)
check("obsolete minimize-to-tray implementation is removed", all(token not in FRONTEND for token in tray_tokens))
check("normal initial maximized presentation remains enabled", "ShowWindow(g_main,SW_MAXIMIZE)" in FRONTEND)

failed = [name for name, ok in checks if not ok]
print(f"SUMMARY {len(checks) - len(failed)}/{len(checks)}")
if failed:
    raise SystemExit(1)
