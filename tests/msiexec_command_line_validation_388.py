from pathlib import Path

root = Path(__file__).resolve().parents[1]
text = (root / "scripts" / "Test-GitHubInstaller.ps1").read_text(encoding="utf-8-sig")
checks: list[bool] = []


def check(condition: bool, label: str) -> None:
    checks.append(condition)
    print(f"{label}: {'PASS' if condition else 'FAIL'}")


check("function Format-NativeArgument" in text, "native argument formatter is explicit")
check("function Quote-NativeArgument" not in text, "blanket quoting helper was removed")
check("if ($Value -notmatch '\\s') { return $Value }" in text, "switches without whitespace remain unquoted")
check("$MsiExecPath = Join-Path $env:SystemRoot 'System32\\msiexec.exe'" in text, "MSI tests use the absolute 64-bit Windows Installer path")
check("-FilePath 'msiexec.exe'" not in text, "MSI tests do not depend on PATH resolution")
check("@('/i', $MsiPath, '/qn', '/norestart', '/L*V!'" in text, "MSI installation uses unquoted switches and flushed verbose logging")
check("@('/fa', $MsiPath, '/qn', '/norestart', '/L*V!'" in text, "MSI repair uses the corrected command-line form")
check("@('/x', $MsiPath, '/qn', '/norestart', '/L*V!'" in text, "MSI removal uses the corrected command-line form")
check(text.count("'REBOOT=ReallySuppress'") >= 4, "all MSI transactions suppress reboot requests explicitly")
check('invalid command line and wait on a hidden usage dialog' in text, "source documents the no-log timeout failure mode")
check("[string]$ExpectedLogPath = ''" in text, "installer process supports an expected startup log")
check("NO LOG: $Description" in text, "missing MSI log is diagnosed before the full process timeout")
check("-ExpectedLogPath $msiInstallLog" in text, "MSI installation requires an early log file")

passed = sum(checks)
print(f"SUMMARY {passed}/{len(checks)}")
raise SystemExit(0 if passed == len(checks) else 1)
