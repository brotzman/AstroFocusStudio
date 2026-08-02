#!/usr/bin/env python3
"""Generate and verify AstroFocus Studio release manifests."""
from __future__ import annotations

import argparse
import hashlib
import os
import re
import sys
from pathlib import Path, PurePosixPath
from typing import Dict, Iterable, List, Tuple

SOURCE_MANIFEST = "SOURCE_SHA256SUMS.txt"
RELEASE_MANIFEST = "SHA256SUMS.txt"
RELEASE_FILES = {
    "AstroFocusStudio.exe": "frontend/AstroFocusStudio.exe",
    "AstroFocusEngine.exe": "backend/AstroFocusEngine.exe",
    "AstroFocusCameraHost.exe": "device_host/AstroFocusCameraHost.exe",
    "AstroFocusFocuserHost.exe": "device_host/AstroFocusFocuserHost.exe",
    "AstroFocusFocuserSetup.exe": "focuser_setup/AstroFocusFocuserSetup.exe",
    "AstroFocusUpdater.exe": "tools/AstroFocusUpdater.exe",
    "AstroFocusSetup.exe": "tools/AstroFocusSetup.exe",
}
EXCLUDED_NAMES = {SOURCE_MANIFEST, RELEASE_MANIFEST, ".DS_Store"}
EXCLUDED_SUFFIXES = {
    ".obj", ".exe", ".pdb", ".ilk", ".exp", ".map", ".log", ".tmp",
    ".bak", ".orig", ".pyc", ".plist", ".d", ".gcda", ".gcno", ".profraw", ".profdata",
}
EXCLUDED_DIRS = {
    ".git", "__pycache__", ".pytest_cache", ".mypy_cache", ".ruff_cache",
    ".clangd", "build", "dist", "out", "analyzer", "analysis-output",
}
LINE_RE = re.compile(r"^([0-9a-f]{64})  (.+)$")


class IntegrityError(RuntimeError):
    pass


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        for block in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def safe_manifest_path(raw: str) -> str:
    if not raw or "\\" in raw or "\x00" in raw:
        raise IntegrityError(f"unsicherer Manifestpfad: {raw!r}")
    posix = PurePosixPath(raw)
    if posix.is_absolute() or any(part in {"", ".", ".."} for part in posix.parts):
        raise IntegrityError(f"unsicherer Manifestpfad: {raw!r}")
    normalized = posix.as_posix()
    if normalized != raw:
        raise IntegrityError(f"nicht normalisierter Manifestpfad: {raw!r}")
    return normalized


def parse_manifest(path: Path) -> Dict[str, str]:
    if not path.is_file():
        raise IntegrityError(f"Manifest fehlt: {path.name}")
    entries: Dict[str, str] = {}
    for line_number, raw_line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        if not raw_line:
            raise IntegrityError(f"leere Manifestzeile in {path.name}:{line_number}")
        match = LINE_RE.fullmatch(raw_line)
        if not match:
            raise IntegrityError(f"ungültige Manifestzeile in {path.name}:{line_number}")
        checksum, raw_name = match.groups()
        name = safe_manifest_path(raw_name)
        if name in entries:
            raise IntegrityError(f"doppelter Eintrag in {path.name}: {name}")
        entries[name] = checksum
    return entries


def is_stable_source(root: Path, path: Path) -> bool:
    rel = path.relative_to(root)
    if path.is_symlink():
        raise IntegrityError(f"symbolischer Link im Paket: {rel.as_posix()}")
    if any(part in EXCLUDED_DIRS for part in rel.parts[:-1]):
        return False
    if rel.name in EXCLUDED_NAMES or rel.suffix.lower() in EXCLUDED_SUFFIXES:
        return False
    # Native test executables are emitted without an extension into tests/.
    if rel.parts and rel.parts[0] == "tests" and rel.suffix == "":
        return False
    return True


def stable_source_files(root: Path) -> List[str]:
    result: List[str] = []
    for path in root.rglob("*"):
        if path.is_dir():
            continue
        if is_stable_source(root, path):
            result.append(path.relative_to(root).as_posix())
    return sorted(result)


def write_manifest(root: Path, name: str, files: Iterable[str]) -> None:
    lines: List[str] = []
    for rel in files:
        safe = safe_manifest_path(rel)
        path = root / Path(*PurePosixPath(safe).parts)
        if not path.is_file() or path.is_symlink():
            raise IntegrityError(f"Datei fehlt oder ist kein regulärer Inhalt: {safe}")
        lines.append(f"{sha256_file(path)}  {safe}\n")
    target = root / name
    temp = target.with_name(target.name + ".tmp")
    temp.write_text("".join(lines), encoding="utf-8", newline="\n")
    os.replace(temp, target)


def write_release_manifest(root: Path) -> None:
    lines: List[str] = []
    for manifest_name, source_name in RELEASE_FILES.items():
        safe_name = safe_manifest_path(manifest_name)
        safe_source = safe_manifest_path(source_name)
        path = root / Path(*PurePosixPath(safe_source).parts)
        if not path.is_file() or path.is_symlink():
            raise IntegrityError(f"Release-Datei fehlt oder ist kein regulärer Inhalt: {safe_source}")
        lines.append(f"{sha256_file(path)}  {safe_name}\n")
    target = root / RELEASE_MANIFEST
    temp = target.with_name(target.name + ".tmp")
    temp.write_text("".join(lines), encoding="utf-8", newline="\n")
    os.replace(temp, target)


def generate(root: Path) -> None:
    write_manifest(root, SOURCE_MANIFEST, stable_source_files(root))
    write_release_manifest(root)


def compare_file_sets(label: str, actual: Dict[str, str], expected: Iterable[str]) -> None:
    actual_set = set(actual)
    expected_set = set(expected)
    missing = sorted(expected_set - actual_set)
    extra = sorted(actual_set - expected_set)
    if missing or extra:
        details: List[str] = []
        if missing:
            details.append("fehlend: " + ", ".join(missing))
        if extra:
            details.append("unerwartet: " + ", ".join(extra))
        raise IntegrityError(f"{label} enthält nicht die erwartete Dateimenge ({'; '.join(details)})")


def verify_entries(root: Path, label: str, entries: Dict[str, str]) -> None:
    for rel, expected in entries.items():
        path = root / Path(*PurePosixPath(rel).parts)
        if not path.is_file() or path.is_symlink():
            raise IntegrityError(f"{label}: Datei fehlt oder ist kein regulärer Inhalt: {rel}")
        actual = sha256_file(path)
        if actual != expected:
            raise IntegrityError(f"{label}: Prüfsumme stimmt nicht: {rel}")


def check_source(root: Path) -> None:
    entries = parse_manifest(root / SOURCE_MANIFEST)
    expected = stable_source_files(root)
    compare_file_sets(SOURCE_MANIFEST, entries, expected)
    verify_entries(root, SOURCE_MANIFEST, entries)


def check_release(root: Path) -> None:
    entries = parse_manifest(root / RELEASE_MANIFEST)
    compare_file_sets(RELEASE_MANIFEST, entries, RELEASE_FILES)
    for manifest_name, expected in entries.items():
        source_name = RELEASE_FILES[manifest_name]
        path = root / Path(*PurePosixPath(source_name).parts)
        if not path.is_file() or path.is_symlink():
            raise IntegrityError(f"{RELEASE_MANIFEST}: Datei fehlt oder ist kein regulärer Inhalt: {source_name}")
        actual = sha256_file(path)
        if actual != expected:
            raise IntegrityError(f"{RELEASE_MANIFEST}: Prüfsumme stimmt nicht: {manifest_name}")


def main(argv: List[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("command", choices=("generate", "check", "check-source", "check-release"))
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    args = parser.parse_args(argv)
    root = args.root.resolve()
    try:
        if args.command == "generate":
            generate(root)
            print("Manifeste erzeugt: PASS")
        elif args.command == "check":
            check_source(root)
            check_release(root)
            print("Quellen- und Releaseintegrität: PASS")
        elif args.command == "check-source":
            check_source(root)
            print("Quellenintegrität: PASS")
        else:
            check_release(root)
            print("Releaseintegrität: PASS")
    except (IntegrityError, OSError, UnicodeError) as exc:
        print(f"Integritätsprüfung: FAIL – {exc}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
