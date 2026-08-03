#!/usr/bin/env python3
"""Remove explicitly allow-listed superseded files and obsolete root-only artifacts.

This is intentionally an allow-list cleanup. It never searches for and deletes
arbitrary files containing an old version string. Generated integrity files are
removed only from the repository root because canonical copies are created in
``dist`` during packaging. Patch readme files are transient exchange-package
metadata and are not part of the product documentation.
"""
from __future__ import annotations

import argparse
from pathlib import Path
import sys

CURRENT_MARKERS = (
    Path("VERSION"),
    Path("KNOWN_LIMITATIONS.txt"),
    Path("RELEASE_NOTES.txt"),
    Path("tests/version_consistency_validation.py"),
)

GENERATED_ROOT_FILES = (
    Path("SHA256SUMS.txt"),
    Path("SOURCE_SHA256SUMS.txt"),
    Path("release-manifest.json"),
)

OBSOLETE_PATCH_FILES = (
    Path("PATCH_README_DE.txt"),
    Path("PATCH_README.txt"),
)

# These files existed before resources were centralized under assets/ and out/.
# They are explicitly allow-listed because copying a clean source archive over an
# existing checkout does not delete formerly tracked files.
DUPLICATE_RESOURCE_FILES = (
    Path("frontend/AstroFocusStudio.ico"),
    Path("backend/AstroFocusStudio.ico"),
    Path("focuser_setup/AstroFocusStudio.ico"),
    Path("frontend/app.res"),
    Path("backend/app.res"),
    Path("focuser_setup/app.res"),
)

LEGACY_FILES = (
    Path("KNOWN_LIMITATIONS_3_9_0.txt"),
    Path("RELEASE_NOTES_3_9_0.txt"),
    Path("tests/version_consistency_validation_390.py"),
    Path("FIXES_3_8_8_REVISION.txt"),
    Path("INSTALLER_FIX_3_8_8.txt"),
    Path("KNOWN_LIMITATIONS_3_8_8.txt"),
    Path("RELEASE_NOTES_3_8_8.txt"),
    Path("tests/actual_backend_validation_388.cpp"),
    Path("tests/build_entrypoints_validation_388.py"),
    Path("tests/command_line_args_validation_388.cpp"),
    Path("tests/continuous_focus_layout_validation_388.py"),
    Path("tests/continuous_focus_logic_validation_388.cpp"),
    Path("tests/continuous_focus_validation_388.py"),
    Path("tests/desktop_shortcut_runtime_validation_388.py"),
    Path("tests/frontend_logic_validation_388.cpp"),
    Path("tests/github_workflow_validation_388.py"),
    Path("tests/healthcheck_cleanup_validation_388.py"),
    Path("tests/installer_bootstrap_validation_388.py"),
    Path("tests/installer_runner_isolation_validation_388.py"),
    Path("tests/installer_smoke_timeout_validation_388.py"),
    Path("tests/installer_updater_concurrency_validation_388.py"),
    Path("tests/msiexec_command_line_validation_388.py"),
    Path("tests/powershell_parameter_binding_validation_388.py"),
    Path("tests/python_runner_diagnostics_validation_388.py"),
    Path("tests/release_integrity_validation_388.py"),
    Path("tests/security_cookie_startup_validation_388.py"),
    Path("tests/security_interlocks_validation_388.py"),
    Path("tests/update_bundle_layout_validation_388.py"),
    Path("tests/updater_version_logic_validation_388.py"),
    Path("tests/window_taskbar_behavior_validation_388.py"),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--root", default=".", help="Repository root")
    parser.add_argument("--log", default="", help="Optional UTF-8 log path")
    parser.add_argument(
        "--check-only",
        action="store_true",
        help="Report obsolete files and fail instead of deleting them",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    root = Path(args.root).resolve()
    lines: list[str] = [f"Repository root: {root}"]

    missing_markers = [str(path) for path in CURRENT_MARKERS if not (root / path).is_file()]
    if missing_markers:
        version = (root / "VERSION").read_text(encoding="utf-8").strip() if (root / "VERSION").is_file() else "unknown"
        lines.append(f"ERROR: current {version} repository markers are missing:")
        lines.extend(f"  - {path}" for path in missing_markers)
        _write_log(args.log, root, lines)
        print("\n".join(lines), file=sys.stderr)
        return 2

    existing_legacy = [path for path in LEGACY_FILES if (root / path).is_file()]
    existing_generated = [path for path in GENERATED_ROOT_FILES if (root / path).is_file()]
    existing_patch = [path for path in OBSOLETE_PATCH_FILES if (root / path).is_file()]
    existing_duplicate_resources = [path for path in DUPLICATE_RESOURCE_FILES if (root / path).is_file()]

    if args.check_only:
        failed = False
        if existing_legacy:
            failed = True
            lines.append("ERROR: superseded 3.8.8 files are still present:")
            lines.extend(f"  - {path}" for path in existing_legacy)
        if existing_generated:
            failed = True
            lines.append("ERROR: generated root artifacts are still present:")
            lines.extend(f"  - {path}" for path in existing_generated)
        if existing_patch:
            failed = True
            lines.append("ERROR: obsolete patch metadata is still present:")
            lines.extend(f"  - {path}" for path in existing_patch)
        if existing_duplicate_resources:
            failed = True
            lines.append("ERROR: duplicate centralized resource files are still present:")
            lines.extend(f"  - {path}" for path in existing_duplicate_resources)
        if failed:
            _write_log(args.log, root, lines)
            print("\n".join(lines), file=sys.stderr)
            return 1
        lines.append("PASS: no superseded files, generated root artifacts, patch metadata, or duplicate resources are present.")
        _write_log(args.log, root, lines)
        print("\n".join(lines))
        return 0

    cleanup_files = LEGACY_FILES + GENERATED_ROOT_FILES + OBSOLETE_PATCH_FILES + DUPLICATE_RESOURCE_FILES
    for relative in cleanup_files:
        candidate = (root / relative).resolve()
        try:
            candidate.relative_to(root)
        except ValueError:
            lines.append(f"ERROR: cleanup path escapes repository root: {relative}")
            _write_log(args.log, root, lines)
            print("\n".join(lines), file=sys.stderr)
            return 3
        if candidate.is_file():
            candidate.unlink()
            lines.append(f"REMOVED: {relative}")

    remaining = [str(path) for path in cleanup_files if (root / path).exists()]
    if remaining:
        lines.append("ERROR: allow-listed files could not be removed:")
        lines.extend(f"  - {path}" for path in remaining)
        _write_log(args.log, root, lines)
        print("\n".join(lines), file=sys.stderr)
        return 4

    lines.append(f"PASS: removed {len(existing_legacy)} superseded 3.8.8 file(s).")
    lines.append(f"PASS: removed {len(existing_generated)} generated root artifact(s).")
    lines.append(f"PASS: removed {len(existing_patch)} obsolete patch metadata file(s).")
    lines.append(f"PASS: removed {len(existing_duplicate_resources)} duplicate centralized resource file(s).")
    _write_log(args.log, root, lines)
    print("\n".join(lines))
    return 0


def _write_log(log_arg: str, root: Path, lines: list[str]) -> None:
    if not log_arg:
        return
    path = Path(log_arg)
    if not path.is_absolute():
        path = root / path
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


if __name__ == "__main__":
    raise SystemExit(main())
