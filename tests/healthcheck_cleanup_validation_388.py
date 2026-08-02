from pathlib import Path

root = Path(__file__).resolve().parents[1]
backend = (root / "backend" / "backend.cpp").read_text(encoding="utf-8-sig")
smoke = (root / "scripts" / "Test-GitHubInstaller.ps1").read_text(encoding="utf-8-sig")
setup = (root / "installer" / "AstroFocusSetup.ps1").read_text(encoding="utf-8-sig")
checks: list[bool] = []

def check(condition: bool, label: str) -> None:
    checks.append(condition)
    print(f"{label}: {'PASS' if condition else 'FAIL'}")

health_start = backend.index("static UINT RunEngineHealthCheck()")
health_end = backend.index('extern "C" void WinMainCRTStartup()', health_start)
health_body = backend[health_start:health_end]

check('../common/command_line_args.inc' in backend, "engine uses the shared exact command-line parser")
check('AfCommandLineArgumentCount(GetCommandLineW(),L"--health-check")' in backend, "engine rejects malformed and duplicate health-check switches")
check('RunHostHealthCheck' not in health_body and 'CreateProcess' not in health_body, "engine self-check no longer starts nested device-host processes")
check('return 21' in health_body and 'return 22' in health_body and 'return 23' in health_body and 'return 24' in health_body, "engine self-check exposes diagnostic exit codes")
check('AstroFocusCameraHost.exe' in health_body and 'AstroFocusFocuserHost.exe' in health_body, "engine self-check verifies both installed host files")
check("@('--health-check')" in smoke and smoke.index("AstroFocusCameraHost.exe") < smoke.index("AstroFocusEngine.exe"), "CI checks device hosts directly before the engine")
check("Bereinigungs-Bundle-Deinstallation" in smoke and "cleanup-bundle-uninstall.log" in smoke, "failure cleanup first uses the owning Burn bundle")
check(smoke.index("Bereinigungs-Bundle-Deinstallation") < smoke.index("Bereinigungs-MSI-Fallback"), "raw MSI cleanup is only a secondary fallback")
check("-TimeoutSeconds 90" in smoke and "-TimeoutSeconds 60" in smoke, "cleanup bundle and MSI fallback have bounded timeouts")
check("Stop-AstroFocusProcesses" in smoke and "Stop-Process -Id" in smoke, "cleanup stops remaining product processes before uninstall")
check(setup.count("--health-check") >= 1 and "AstroFocusCameraHost.exe','AstroFocusFocuserHost.exe','AstroFocusEngine.exe" in setup, "development installer validates all three runtime executables separately")

passed = sum(checks)
print(f"SUMMARY {passed}/{len(checks)}")
raise SystemExit(0 if passed == len(checks) else 1)
