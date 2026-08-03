from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
FRONTEND = (ROOT / "frontend" / "frontend.cpp").read_text(encoding="utf-8")
KERNEL_DEF = (ROOT / "frontend" / "kernel32.def").read_text(encoding="utf-8")
SMOKE = (ROOT / "scripts" / "Test-GitHubInstaller.ps1").read_text(encoding="utf-8")
WORKFLOW = (ROOT / ".github" / "workflows" / "windows-build.yml").read_text(encoding="utf-8")
NATIVE = (ROOT / "tests" / "frontend_logic_validation.cpp").read_text(encoding="utf-8")

checks: list[tuple[str, bool]] = []

def check(name: str, condition: bool) -> None:
    checks.append((name, bool(condition)))

app_main = FRONTEND.split('extern "C" void AstroFocusApplicationMain(){', 1)[1]
show_pos = app_main.find("ShowWindow(g_main,SW_MAXIMIZE)")
post_pos = app_main.find("PostMessageW(g_main,WM_APP_START_ENGINE")
direct_start_pos = app_main.find("StartEngineAfterWindowShown()")

check("frontend diagnostics use a writable per-user location", 'GetEnvironmentVariableW(L"LOCALAPPDATA"' in FRONTEND and 'AstroFocusStudio")' in FRONTEND and 'FrontendTrace.log' in FRONTEND)
check("diagnostics have a temporary-directory fallback", "GetTempPathW(520,root)" in FRONTEND)
check("diagnostic file permits concurrent CI reads", "FILE_SHARE_READ|FILE_SHARE_WRITE" in FRONTEND)
check("trace writer never formats an exception string into a fixed line buffer", "char line[420]" not in FRONTEND and "textLength<2048U" in FRONTEND and "WriteAllHandle(h,text,textLength)" in FRONTEND)
check("crash dialog has room for phase and full diagnostic path", "wchar_t message[1400]" in FRONTEND)
check("main window is shown before deferred engine startup", show_pos >= 0 and post_pos > show_pos)
check("engine startup is dispatched through a dedicated window message", "#define WM_APP_START_ENGINE" in FRONTEND and "if(m==WM_APP_START_ENGINE){StartEngineAfterWindowShown();return 0;}" in FRONTEND)
check("startup no longer blocks invisibly before ShowWindow", "if(!StartEngine())" not in app_main[:show_pos])
check("winsock failure leaves the diagnostic window open", "g_winsockReady=InitWinsock()" in app_main and "Winsock initialization failed" in app_main and "ExitProcess(4)" not in app_main)
check("window registration failure is visible and logged", "FailFrontendStartup(\"window class registration failed\"" in FRONTEND)
check("main-window creation failure is visible and logged", "FailFrontendStartup(\"main window creation failed\"" in FRONTEND)
check("child-control creation failures are counted", "g_controlCreationFailures++" in FRONTEND and "child control creation failed" in FRONTEND)
check("unhandled startup faults display the phase and log path", "AstroFocus Studio – Programmfehler" in FRONTEND and "g_frontendPhase" in FRONTEND and "g_frontendLogPath" in FRONTEND)
check("crash dialog converts the startup phase explicitly to Unicode", "AToW(g_frontendPhase?g_frontendPhase" in FRONTEND and "Phase: %s" in FRONTEND and "Phase: %S" not in FRONTEND)
check("startup failure preserves the original Windows error code", "DWORD error=GetLastError();AppendFrontendTrace(trace)" in FRONTEND and ",error,g_frontendLogPath" in FRONTEND)
check("startup phases identify resources, controls, display and network", all(phase in app_main for phase in ('SetFrontendPhase("resource initialization")', 'SetFrontendPhase("child control creation")', 'SetFrontendPhase("window display")', 'SetFrontendPhase("Winsock initialization")')))
check("message-loop failure is distinguished from normal exit", "if(messageResult<0)" in app_main and "GetMessage failed" in app_main)
check("new diagnostics imports are present in the import definition", all(name in KERNEL_DEF for name in ("GetEnvironmentVariableW", "CreateDirectoryW", "GetLastError")))
check("native frontend test constructs the complete control tree", "CreateControls();" in NATIVE and "Frontend startup: all controls created in native harness" in NATIVE)
check("installer smoke test starts the installed GUI", "function Invoke-FrontendStartupCheck" in SMOKE and "AstroFocusStudio.exe" in SMOKE)
check("GUI smoke test requires the real main-window title", "MainWindowHandle" in SMOKE and '"AstroFocus Studio $ProductVersion*"' in SMOKE)
check("GUI smoke test detects an early process exit", "wurde während des Starts beendet" in SMOKE and "wurde kurz nach dem sichtbaren Start beendet" in SMOKE)
check("GUI smoke test verifies responsiveness with a bounded engine-start window", ".Responding" in SMOKE and "$responsiveDeadline" in SMOKE and "AddSeconds(15)" in SMOKE)
check("GUI smoke test verifies graceful WM_CLOSE shutdown", ".CloseMainWindow()" in SMOKE and "WaitForExit(15000)" in SMOKE)
check("GUI crash diagnostics and application events are uploaded", "frontend-trace.log" in SMOKE and "frontend-application-events.log" in SMOKE)
check("GUI smoke cleanup is safe when process creation fails", "$started = $false" in SMOKE and "$started = $true" in SMOKE and "if ($started -and -not $process.HasExited)" in SMOKE)
check("both isolated installer modes run the GUI smoke test", SMOKE.count("Invoke-FrontendStartupCheck") == 3)
check("workflow preflight includes current frontend import and build definitions", "frontend\\build-windows-x64.bat" in WORKFLOW and "frontend\\kernel32.def" in WORKFLOW)
check("workflow preflight includes the startup regression", "tests\\frontend_startup_resilience_validation.py" in WORKFLOW)

passed = 0
for name, ok in checks:
    print(f"{name}: {'PASS' if ok else 'FAIL'}")
    passed += int(ok)
print(f"SUMMARY {passed}/{len(checks)}")
raise SystemExit(0 if passed == len(checks) else 1)
