from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
PRODUCT_VERSION = "3.9.0"
BUNDLE_VERSION = "3.9.0.0"
TAG = "v3.9.0"
TEST_SUFFIX = "_390"

checks: list[tuple[str, bool]] = []

def check(name: str, condition: bool) -> None:
    checks.append((name, bool(condition)))
    print(f"{name}: {'PASS' if condition else 'FAIL'}")

def read(relative: str) -> str:
    return (ROOT / relative).read_text(encoding="utf-8-sig")

workflow = read(".github/workflows/windows-build.yml")
frontend = read("frontend/frontend.cpp")
backend = read("backend/backend.cpp")
updater = read("updater/AstroFocusUpdater.ps1")
build_artifacts = read("scripts/Build-GitHubArtifacts.ps1")
wix_build = read("installer/build-wix.ps1")
installer_test = read("scripts/Test-GitHubInstaller.ps1")
release_manifest = read("release/New-ReleaseManifest.ps1")
update_manifest = read("release/New-UpdateManifest.ps1")
package = read("installer/wix/Package.wxs")

check("workflow product version is 3.9.0", "PRODUCT_VERSION: '3.9.0'" in workflow)
check("workflow bundle version is 3.9.0.0", "BUNDLE_VERSION: '3.9.0.0'" in workflow)
check("manual release tag defaults to v3.9.0", "default: 'v3.9.0'" in workflow)
check("artifact builder defaults to product version 3.9.0", "[string]$ProductVersion = '3.9.0'" in build_artifacts)
check("artifact builder defaults to bundle version 3.9.0.0", "[string]$BundleVersion = '3.9.0.0'" in build_artifacts)
check("WiX builder defaults to product version 3.9.0", "[string]$ProductVersion = '3.9.0'" in wix_build)
check("WiX builder defaults to bundle version 3.9.0.0", "[string]$BundleVersion = '3.9.0.0'" in wix_build)
check("installer smoke test defaults to 3.9.0", "[string]$ProductVersion = '3.9.0'" in installer_test)
check("release manifest defaults to 3.9.0", "[string]$Version='3.9.0'" in release_manifest)
check("updater bundled version is 3.9.0", "$BundledVersion = [version]'3.9.0'" in updater)
check("frontend requires engine version 3.9.0", 'WEqual(g_state.version,L"3.9.0")' in frontend)
check("frontend title is 3.9.0", 'L"AstroFocus Studio 3.9.0"' in frontend)
check("backend status API reports 3.9.0", '"version":"3.9.0"' in backend.replace('\\"', '"'))
check("known limitations payload uses 3.9.0 file", "KNOWN_LIMITATIONS_3_9_0.txt" in build_artifacts and "KNOWN_LIMITATIONS_3_9_0.txt" in package)
check("update manifest remains compatible with older 3.8.x installs", "MinimumSupportedVersion='3.8.1'" in update_manifest)
check("release notes for 3.9.0 exist", (ROOT / "RELEASE_NOTES_3_9_0.txt").is_file())
check("known limitations for 3.9.0 exist", (ROOT / "KNOWN_LIMITATIONS_3_9_0.txt").is_file())
check("workflow preflight includes version consistency test", "tests\\version_consistency_validation_390.py" in workflow)
run_python = read("scripts/Run-PythonTests.ps1")
cleanup_script = read("scripts/remove_legacy_version_files.py")
check("Python runner executes only the 3.9.0 test suite", "$currentSuffix = '_390.py'" in run_python)
check("Python runner executes version consistency first", "$versionTest + $remainingTests" in run_python)
check("legacy cleanup is allow-list based", "LEGACY_FILES = (" in cleanup_script)
check("workflow invokes legacy cleanup", "Remove superseded version files" in workflow)

text_extensions = {".cpp", ".h", ".inc", ".py", ".ps1", ".bat", ".cmd", ".sh", ".md", ".txt", ".yml", ".yaml", ".json", ".wxs", ".def"}
stale_hits: list[str] = []
allowed_legacy_reference_paths = {
    Path(__file__).resolve(),
    (ROOT / "scripts/remove_legacy_version_files.py").resolve(),
    (ROOT / "tests/legacy_version_cleanup_validation_390.py").resolve(),
    (ROOT / "docs/GITHUB_ACTIONS_VERSION_CLEANUP_DE.md").resolve(),
}
for path in ROOT.rglob("*"):
    if path.resolve() in allowed_legacy_reference_paths or not path.is_file() or path.suffix.lower() not in text_extensions:
        continue
    try:
        content = path.read_text(encoding="utf-8-sig")
    except UnicodeDecodeError:
        continue
    if re.search(r"3\.8\.8|3_8_8|_388|3\\\.8\\\.8", content):
        stale_hits.append(str(path.relative_to(ROOT)))
check("no stale 3.8.8 version references remain", not stale_hits)
if stale_hits:
    print("STALE:", ", ".join(stale_hits))

stale_names = [
    str(path.relative_to(ROOT))
    for path in ROOT.rglob("*")
    if path.is_file() and ("3_8_8" in path.name or "_388" in path.name)
]
check("no stale 3.8.8 versioned filenames remain", not stale_names)
if stale_names:
    print("STALE NAMES:", ", ".join(stale_names))

versioned_tests = sorted((ROOT / "tests").glob("*validation_*.py")) + sorted((ROOT / "tests").glob("*validation_*.cpp"))
check("all versioned regression tests use the 3.9.0 suffix", bool(versioned_tests) and all(TEST_SUFFIX in p.stem for p in versioned_tests))

failed = [name for name, ok in checks if not ok]
print(f"SUMMARY {len(checks) - len(failed)}/{len(checks)}")
raise SystemExit(1 if failed else 0)
