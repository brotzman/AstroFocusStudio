from pathlib import Path

root = Path(__file__).resolve().parents[1]
text = (root / "scripts" / "Test-GitHubInstaller.ps1").read_text(encoding="utf-8-sig")
checks = []

def check(condition: bool, label: str) -> None:
    checks.append(condition)
    print(f"{label}: {'PASS' if condition else 'FAIL'}")

check("Start-Process -FilePath" not in text and "-Wait -PassThru" not in text, "installer smoke test avoids Start-Process descendant-tree waits")
check("System.Diagnostics.ProcessStartInfo" in text, "installer smoke test uses a direct process handle")
check("WaitForExit($TimeoutSeconds * 1000)" in text, "every external installer process has a bounded wait")
check("taskkill.exe /PID $ProcessId /T /F" in text, "timed-out process trees are terminated")
check("installer-smoke.log" in text, "installer smoke test writes a persistent phase log")
check("-TimeoutSeconds 30" in text, "installed health checks use a short explicit timeout")
check("-TimeoutSeconds 180" in text, "bundle and MSI operations use bounded timeouts")
check("'/install'" not in text, "unsupported WixStdBA install switch is removed")
check("START: $Description" in text and "END: $Description" in text, "each installer phase records start and completion")
check("Details: $SmokeLog" in text, "timeout and exit errors point to the diagnostic log")

passed = sum(checks)
print(f"SUMMARY {passed}/{len(checks)}")
raise SystemExit(0 if passed == len(checks) else 1)
