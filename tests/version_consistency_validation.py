from __future__ import annotations

import importlib.util
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
checks: list[tuple[str, bool]] = []


def check(name: str, condition: bool) -> None:
    checks.append((name, bool(condition)))
    print(f"{name}: {'PASS' if condition else 'FAIL'}")


def read(relative: str) -> str:
    return (ROOT / relative).read_text(encoding="utf-8-sig")


version = read("VERSION").strip()
match = re.fullmatch(r"(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)", version)
check("VERSION contains a valid semantic product version", match is not None)
check("VERSION is normalized to one line", read("VERSION") == version + "\n")

with tempfile.TemporaryDirectory() as temporary:
    generated = Path(temporary) / "version.h"
    result = subprocess.run(
        [
            sys.executable,
            str(ROOT / "tools/generate_version.py"),
            "--version-file",
            str(ROOT / "VERSION"),
            "--header",
            str(generated),
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    check("version header generator succeeds", result.returncode == 0)
    check("committed version header is generated from VERSION", generated.read_bytes() == (ROOT / "common/version.h").read_bytes())

frontend = read("frontend/frontend.cpp")
backend = read("backend/backend.cpp")
check("frontend includes the generated version header", '#include "../common/version.h"' in frontend)
check("backend includes the generated version header", '#include "../common/version.h"' in backend)
check("frontend version handshake uses the central macro", "WEqual(g_state.version,AFS_VERSION_TEXT_W)" in frontend)
check("frontend window title uses the central macro", "AFS_FRONTEND_TITLE_W,WS_OVERLAPPED" in frontend)
check("backend status uses the central macro", '"version":"" AFS_VERSION_TEXT_A' in backend.replace('\\"', '"'))

workflow = read(".github/workflows/windows-build.yml")
check("workflow reads VERSION in a metadata job", "name: Read repository version" in workflow and "< VERSION" in workflow)
check("workflow has no hard-coded product or bundle version environment", "PRODUCT_VERSION: '" not in workflow and "BUNDLE_VERSION: '" not in workflow)
check("workflow release tag defaults from VERSION", "needs.metadata.outputs.tag" in workflow)

build_artifacts = read("scripts/Build-GitHubArtifacts.ps1")
wix_build = read("installer/build-wix.ps1")
installer_test = read("scripts/Test-GitHubInstaller.ps1")
release_manifest = read("release/New-ReleaseManifest.ps1")
check("artifact builder resolves empty versions from VERSION", "Get-RepositoryVersion.ps1" in build_artifacts and "[string]$ProductVersion = ''" in build_artifacts)
check("WiX builder resolves empty versions from VERSION", "Get-RepositoryVersion.ps1" in wix_build and "[string]$ProductVersion = ''" in wix_build)
check("installer test resolves empty version from VERSION", "Get-RepositoryVersion.ps1" in installer_test and "[string]$ProductVersion = ''" in installer_test)
check("release manifest resolves empty version from VERSION", "Get-RepositoryVersion.ps1" in release_manifest and "[string]$Version=''" in release_manifest)

check("release notes use a stable filename", (ROOT / "RELEASE_NOTES.txt").is_file() and not list(ROOT.glob("RELEASE_NOTES_*.*")))
check("known limitations use a stable filename", (ROOT / "KNOWN_LIMITATIONS.txt").is_file() and not list(ROOT.glob("KNOWN_LIMITATIONS_*.*")))
versioned_tests = sorted((ROOT / "tests").glob("*validation_*.*"))
check("regression test filenames are version-independent", not versioned_tests)
run_python = read("scripts/Run-PythonTests.ps1")
run_native = read("scripts/Run-NativeTests.sh")
check("Python runner discovers stable test names", "*_validation.py" in run_python and "_390" not in run_python)
check("native runner uses stable test names", "_validation.cpp" in run_native and "_390" not in run_native)

active_files = [
    "build-windows-x64.sh",
    "build-all-windows-x64.bat",
    "frontend/frontend.cpp",
    "backend/backend.cpp",
    "installer/AstroFocusSetup.ps1",
    "installer/build-wix.ps1",
    "scripts/Build-GitHubArtifacts.ps1",
    "scripts/Test-GitHubInstaller.ps1",
    "release/New-ReleaseManifest.ps1",
    "updater/AstroFocusUpdater.ps1",
]
hardcoded = [name for name in active_files if version in read(name)]
check("active build and runtime files do not hard-code the current version", not hardcoded)
if hardcoded:
    print("HARDCODED:", ", ".join(hardcoded))

failed = [name for name, ok in checks if not ok]
print(f"SUMMARY {len(checks) - len(failed)}/{len(checks)}")
raise SystemExit(1 if failed else 0)
