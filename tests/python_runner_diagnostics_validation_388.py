#!/usr/bin/env python3
"""Contract checks for complete Python-test diagnostics on Windows PowerShell 5.1."""
from pathlib import Path
import sys

root = Path(__file__).resolve().parents[1]
runner = (root / "scripts" / "Run-PythonTests.ps1").read_text(encoding="utf-8-sig")
workflow = (root / ".github" / "workflows" / "windows-build.yml").read_text(encoding="utf-8-sig")
validator = (root / "tests" / "github_workflow_validation_388.py").read_text(encoding="utf-8-sig")
builder = (root / "scripts" / "Build-GitHubArtifacts.ps1").read_text(encoding="utf-8-sig")

required_block = workflow.split("$requiredFiles = @(", 1)[1].split("$optionalMetadata", 1)[0]

checks = [
    ("Start-Process" in runner, "runner uses Process execution instead of a native stderr pipeline"),
    ("RedirectStandardOutput" in runner, "runner captures complete stdout"),
    ("RedirectStandardError" in runner, "runner captures complete stderr/tracebacks"),
    ("-X', 'utf8'" in runner, "Python runs in deterministic UTF-8 mode"),
    ("python-tests.log" in runner and "python-tests.log" in builder, "complete Python log is preserved under CI diagnostics"),
    ("installer\\wix\\Package.wxs" in workflow, "preflight requires Package.wxs"),
    ("installer\\wix\\Bundle.wxs" in workflow, "preflight requires Bundle.wxs"),
    ("KNOWN_LIMITATIONS_3_8_8.txt" in required_block, "preflight requires the current known-limitations payload"),
    ("UNSIGNED_DEVELOPMENT_BUILD.txt" in required_block, "preflight requires the unsigned-development marker"),
    ("updater\\update-public-key.cer" in required_block, "preflight requires the updater public key"),
    ("Assert-PackagingInputs" in builder, "local artifact builds validate payload inputs before compilation"),
    (".gitattributes" not in required_block and ".gitignore" not in required_block, "repository metadata files are not build prerequisites"),
    ("$optionalMetadata = @('.gitattributes', '.gitignore')" in workflow, "missing repository metadata is checked separately"),
    ("Optional repository metadata is missing and will not block the build" in workflow, "missing repository metadata only produces a warning"),
    (workflow.index("Prepare CI diagnostics") < workflow.index("Verify repository build entry points"), "preflight diagnostics are initialized before validation"),
    ("preflight.log" in workflow, "preflight output is persisted for failed runs"),
    ("if-no-files-found: warn" in workflow, "log upload does not mask the primary failure"),
    ("required GitHub/WiX or payload source files are missing" in validator, "validator reports missing build and payload inputs without a traceback"),
    ("utf-8-sig" in validator, "validator accepts normal UTF-8 and UTF-8 BOM files"),
]

passed = 0
for condition, message in checks:
    if condition:
        passed += 1
        print(f"{message}: PASS")
    else:
        print(f"{message}: FAIL")
print(f"SUMMARY {passed}/{len(checks)}")
sys.exit(0 if passed == len(checks) else 1)
