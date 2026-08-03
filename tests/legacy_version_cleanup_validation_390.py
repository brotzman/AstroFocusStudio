from pathlib import Path
import ast

ROOT = Path(__file__).resolve().parents[1]
cleanup_path = ROOT / "scripts/remove_legacy_version_files.py"
runner_path = ROOT / "scripts/Run-PythonTests.ps1"
workflow_path = ROOT / ".github/workflows/windows-build.yml"
cleanup = cleanup_path.read_text(encoding="utf-8-sig")
runner = runner_path.read_text(encoding="utf-8-sig")
workflow = workflow_path.read_text(encoding="utf-8-sig")
launcher = (ROOT / "Cleanup-Legacy-Version-Files.cmd").read_text(encoding="utf-8-sig")

checks: list[tuple[str, bool]] = []

def check(name: str, condition: bool) -> None:
    checks.append((name, bool(condition)))
    print(f"{name}: {'PASS' if condition else 'FAIL'}")

ast.parse(cleanup)
check("legacy cleanup script is valid Python", True)
check("cleanup is restricted to an explicit allow-list", "LEGACY_FILES = (" in cleanup)
check("cleanup verifies current 3.9.0 markers", "CURRENT_MARKERS = (" in cleanup and "KNOWN_LIMITATIONS_3_9_0.txt" in cleanup)
check("cleanup includes obsolete 3.8.8 root payloads", all(name in cleanup for name in (
    "FIXES_3_8_8_REVISION.txt", "INSTALLER_FIX_3_8_8.txt",
    "KNOWN_LIMITATIONS_3_8_8.txt", "RELEASE_NOTES_3_8_8.txt")))
check("cleanup includes obsolete 3.8.8 Python contract test", "tests/github_workflow_validation_388.py" in cleanup)
check("cleanup includes obsolete 3.8.8 native tests", all(name in cleanup for name in (
    "tests/command_line_args_validation_388.cpp",
    "tests/frontend_logic_validation_388.cpp",
    "tests/actual_backend_validation_388.cpp")))
check("cleanup rejects paths outside the repository", "candidate.relative_to(root)" in cleanup)
check("Python runner invokes legacy cleanup before test discovery", runner.index("remove_legacy_version_files.py") < runner.index("Get-ChildItem"))
check("Python runner selects only 3.9.0 tests", "$currentSuffix = '_390.py'" in runner)
check("version consistency runs before remaining tests", "$versionTest + $remainingTests" in runner)
check("workflow runs legacy cleanup before repository preflight", workflow.index("Remove superseded version files") < workflow.index("Verify repository build entry points"))
check("workflow requires the cleanup script", "scripts\\remove_legacy_version_files.py" in workflow)
check("cleanup diagnostics are persisted", "legacy-version-cleanup.log" in workflow and "legacy-version-cleanup.log" in runner)
check("workflow cleanup suppresses Python bytecode", "python -B -X utf8 $cleanupScript" in workflow)
check("test-runner cleanup suppresses Python bytecode", "'-B', '-X', 'utf8'" in runner)
check("Windows cleanup launcher invokes the allow-list cleanup", "remove_legacy_version_files.py --root ." in launcher)
check("Windows cleanup launcher reminds Git to record deletions", "git add -A" in launcher)

passed = sum(ok for _, ok in checks)
print(f"SUMMARY {passed}/{len(checks)}")
raise SystemExit(0 if passed == len(checks) else 1)
