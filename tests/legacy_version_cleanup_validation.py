from pathlib import Path
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
cleanup_path = ROOT / "scripts" / "remove_legacy_version_files.py"
cleanup = cleanup_path.read_text(encoding="utf-8")
runner = (ROOT / "scripts" / "Run-PythonTests.ps1").read_text(encoding="utf-8")
workflow = (ROOT / ".github" / "workflows" / "windows-build.yml").read_text(encoding="utf-8")
checks = []

def check(name: str, ok: bool) -> None:
    checks.append(ok)
    print(f"{name}: {'PASS' if ok else 'FAIL'}")

check("cleanup is allow-list based", "LEGACY_FILES = (" in cleanup and "rglob" not in cleanup)
check("cleanup preserves central repository markers", all(name in cleanup for name in ("VERSION", "KNOWN_LIMITATIONS.txt", "RELEASE_NOTES.txt", "version_consistency_validation.py")))
check("cleanup removes formerly versioned current payload names", all(name in cleanup for name in ("KNOWN_LIMITATIONS_3_9_0.txt", "RELEASE_NOTES_3_9_0.txt", "version_consistency_validation_390.py")))
check("cleanup includes obsolete 3.8.8 root payloads", all(name in cleanup for name in ("FIXES_3_8_8_REVISION.txt", "INSTALLER_FIX_3_8_8.txt", "KNOWN_LIMITATIONS_3_8_8.txt", "RELEASE_NOTES_3_8_8.txt")))
check("cleanup checks patch metadata in check-only mode", "obsolete patch metadata is still present" in cleanup)
check("Python runner invokes cleanup before test discovery", runner.index("remove_legacy_version_files.py") < runner.index("Get-ChildItem"))
check("Python runner discovers stable validation names", "*_validation.py" in runner and "_390.py" not in runner)
check("version consistency runs before remaining tests", "$versionTest + $remainingTests" in runner)
check("workflow runs cleanup before repository preflight", workflow.index("Remove superseded version files") < workflow.index("Verify repository build entry points"))
check("workflow cleanup suppresses Python bytecode", "python -B -X utf8" in workflow)

with tempfile.TemporaryDirectory() as temporary:
    temp_root = Path(temporary)
    for marker, content in (
        ("VERSION", "3.9.0\n"), ("KNOWN_LIMITATIONS.txt", "stable\n"),
        ("RELEASE_NOTES.txt", "stable\n"), ("tests/version_consistency_validation.py", "stable\n"),
    ):
        target = temp_root / marker; target.parent.mkdir(parents=True, exist_ok=True); target.write_text(content, encoding="utf-8")
    for generated in ("SHA256SUMS.txt", "SOURCE_SHA256SUMS.txt", "release-manifest.json", "PATCH_README_DE.txt", "PATCH_README.txt"):
        (temp_root / generated).write_text("stale\n", encoding="utf-8")
    old_current = temp_root / "KNOWN_LIMITATIONS_3_9_0.txt"; old_current.write_text("legacy\n", encoding="utf-8")
    legacy = temp_root / "KNOWN_LIMITATIONS_3_8_8.txt"; legacy.write_text("legacy\n", encoding="utf-8")
    result = subprocess.run([sys.executable, "-B", "-X", "utf8", str(cleanup_path), "--root", str(temp_root)], capture_output=True, text=True)
    check("functional cleanup succeeds", result.returncode == 0)
    check("functional cleanup removes generated root artifacts", not (temp_root / "SHA256SUMS.txt").exists())
    check("functional cleanup removes patch metadata", not (temp_root / "PATCH_README_DE.txt").exists())
    check("functional cleanup removes old stable-name predecessors", not old_current.exists())
    check("functional cleanup removes obsolete payloads", not legacy.exists())
    check("functional cleanup preserves central markers", all((temp_root / marker).is_file() for marker in ("VERSION", "KNOWN_LIMITATIONS.txt", "RELEASE_NOTES.txt", "tests/version_consistency_validation.py")))

print(f"SUMMARY {sum(checks)}/{len(checks)}")
raise SystemExit(0 if all(checks) else 1)
