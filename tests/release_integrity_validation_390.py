from pathlib import Path
import sys
sys.dont_write_bytecode = True
import importlib.util
import tempfile

root = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("release_integrity", root / "tools" / "release_integrity.py")
module = importlib.util.module_from_spec(spec)
assert spec.loader is not None
spec.loader.exec_module(module)

checks = {}
checks["all seven shipped executables are covered"] = set(module.RELEASE_FILES) == {
    "AstroFocusStudio.exe", "AstroFocusEngine.exe", "AstroFocusCameraHost.exe",
    "AstroFocusFocuserHost.exe", "AstroFocusFocuserSetup.exe",
    "AstroFocusUpdater.exe", "AstroFocusSetup.exe",
}
checks["release manifest uses flat payload names"] = all("/" not in name and "\\" not in name for name in module.RELEASE_FILES)
checks["source paths point to existing binaries"] = all((root / source).is_file() for source in module.RELEASE_FILES.values())
checks["temporary original backups are excluded"] = ".orig" in module.EXCLUDED_SUFFIXES
checks["compiled outputs are excluded from source manifest"] = all(suffix in module.EXCLUDED_SUFFIXES for suffix in (".obj", ".exe"))

with tempfile.TemporaryDirectory() as temporary:
    work = Path(temporary)
    for manifest_name, source_name in module.RELEASE_FILES.items():
        path = work / source_name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes((manifest_name + "\n").encode("ascii"))
    module.write_release_manifest(work)
    entries = module.parse_manifest(work / module.RELEASE_MANIFEST)
    checks["generated release manifest has exact flat names"] = set(entries) == set(module.RELEASE_FILES)
    try:
        module.check_release(work)
        checks["generated release manifest verifies against mapped files"] = True
    except module.IntegrityError:
        checks["generated release manifest verifies against mapped files"] = False

for name, ok in checks.items():
    print(f"{name}: {'PASS' if ok else 'FAIL'}")
print(f"SUMMARY {sum(checks.values())}/{len(checks)}")
raise SystemExit(0 if all(checks.values()) else 1)
