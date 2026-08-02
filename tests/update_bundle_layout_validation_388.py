from pathlib import Path
import tempfile

root = Path(__file__).resolve().parents[1]
updater = (root / "updater" / "AstroFocusUpdater.ps1").read_text(encoding="utf-8")

checks = {
    "bundle selection checks setup script sibling": "Join-Path $candidate 'AstroFocusSetup.ps1'" in updater,
    "bundle selection checks payload sibling": "Join-Path $candidate 'payload'" in updater,
    "bundle selection requires complete bundle": "genau ein vollständiges Setup-Bundle" in updater,
    "legacy global setup count removed": "genau ein AstroFocusSetup.exe" not in updater,
    "candidate roots are deduplicated": "Sort-Object -Unique" in updater,
}

# Model the intended layout test independently of PowerShell: a complete bundle
# legitimately contains a second installed copy of AstroFocusSetup.exe in payload.
def find_complete_bundle_roots(base: Path):
    roots = set()
    for setup in base.rglob("AstroFocusSetup.exe"):
        candidate = setup.parent
        if (candidate / "AstroFocusSetup.ps1").is_file() and (candidate / "payload").is_dir():
            roots.add(candidate.resolve())
    return roots

with tempfile.TemporaryDirectory() as temporary:
    stage = Path(temporary)
    bundle = stage / "AstroFocusStudio-3.8.8-Setup"
    payload = bundle / "payload"
    payload.mkdir(parents=True)
    for path in (
        bundle / "AstroFocusSetup.exe",
        bundle / "AstroFocusSetup.ps1",
        payload / "AstroFocusSetup.exe",
        payload / "AstroFocusSetup.ps1",
    ):
        path.write_bytes(b"test")
    roots = find_complete_bundle_roots(stage)
    checks["standard bundle with payload setup resolves once"] = roots == {bundle.resolve()}

    rogue = stage / "rogue"
    (rogue / "payload").mkdir(parents=True)
    (rogue / "AstroFocusSetup.exe").write_bytes(b"test")
    (rogue / "AstroFocusSetup.ps1").write_bytes(b"test")
    roots = find_complete_bundle_roots(stage)
    checks["two complete bundle roots are rejected"] = len(roots) == 2

for name, ok in checks.items():
    print(f"{name}: {'PASS' if ok else 'FAIL'}")
print(f"SUMMARY {sum(checks.values())}/{len(checks)}")
raise SystemExit(0 if all(checks.values()) else 1)
