from pathlib import Path

root = Path(__file__).resolve().parents[1]
workflow = (root / ".github" / "workflows" / "windows-build.yml").read_text(encoding="utf-8-sig")
smoke = (root / "scripts" / "Test-GitHubInstaller.ps1").read_text(encoding="utf-8-sig")
checks: list[bool] = []

def check(condition: bool, label: str) -> None:
    checks.append(condition)
    print(f"{label}: {'PASS' if condition else 'FAIL'}")

check("bundle-test:" in workflow, "workflow has a dedicated Burn bundle job")
check("msi-test:" in workflow, "workflow has a dedicated raw MSI job")
check("Test Burn bundle on clean Windows runner" in workflow, "bundle test documents clean-runner isolation")
check("Test raw MSI on clean Windows runner" in workflow, "MSI test documents clean-runner isolation")
check("-Mode Bundle" in workflow, "bundle job invokes bundle-only smoke mode")
check("-Mode Msi" in workflow, "MSI job invokes MSI-only smoke mode")
check("Installer-Test-Input" in workflow, "built packages are transferred to isolated test runners")
check("Stage isolated installer-test package" in workflow, "build job stages deterministic test input")
check("needs: [metadata, windows-build, bundle-test, msi-test]" in workflow, "release waits for both isolated installer tests")
check("[ValidateSet('Bundle', 'Msi')]" in smoke, "smoke script rejects mixed or unknown modes")
check("if ($Mode -eq 'Bundle')" in smoke, "smoke script separates bundle and MSI paths")
check("MSI-Reparatur" in smoke and "'/fa'" in smoke, "raw MSI receives an independent repair test")
check("Never run this immediately after a Burn transaction" in smoke, "source records the Windows Installer isolation invariant")
check("PASS: Bundle install" in smoke and "PASS: MSI install" in smoke, "each isolated mode has an explicit completion result")

passed = sum(checks)
print(f"SUMMARY {passed}/{len(checks)}")
raise SystemExit(0 if passed == len(checks) else 1)
