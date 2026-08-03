#!/usr/bin/env python3
"""Prevent Git Bash/MSYS from rewriting MSVC-style /options into paths."""
from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BUILD = ROOT / "build-windows-x64.sh"
text = BUILD.read_text(encoding="utf-8")

# Git for Windows path conversion treats arguments such as /nologo as POSIX
# paths and can rewrite them to C:/Program Files/Git/nologo.  Native LLVM
# tools accept the equivalent -option spelling, which is safe in Git Bash.
native_lines = [
    line.strip()
    for line in text.splitlines()
    if '"$CLANG_CL"' in line or '"$LLD_LINK"' in line or "local args=(" in line or "args+=(" in line
]
joined = "\n".join(native_lines)

slash_switch = re.compile(r"(?<![A-Za-z0-9_])/[A-Za-z][A-Za-z0-9_-]*(?::|\b)")
violations = sorted(set(slash_switch.findall(joined)))

checks = {
    "central Bash build invokes clang-cl": '"$CLANG_CL"' in text,
    "central Bash build invokes lld-link": '"$LLD_LINK"' in text,
    "clang-cl uses MSYS-safe -nologo": '"$CLANG_CL" -nologo' in text,
    "lld-link uses MSYS-safe -nologo": '"$LLD_LINK" -nologo' in text,
    "link argument array uses dash-prefixed COFF options": "local args=(-nologo -machine:x64" in text,
    "no MSVC-style slash switch reaches native LLVM from Bash": not violations,
    "no global path-conversion disable masks path bugs": "MSYS2_ARG_CONV_EXCL=*" not in text and "MSYS_NO_PATHCONV=1" not in text,
}

for name, ok in checks.items():
    detail = f" ({', '.join(violations)})" if name.startswith("no MSVC") and violations else ""
    print(f'{name}: {"PASS" if ok else "FAIL"}{detail}')
print(f"SUMMARY {sum(checks.values())}/{len(checks)}")
raise SystemExit(0 if all(checks.values()) else 1)
