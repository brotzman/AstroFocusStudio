#!/usr/bin/env python3
"""Run source-level and optional post-build Python regression tests."""
from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
TESTS = ROOT / "tests"
POST_BUILD_TESTS = {
    "installer_bootstrap_validation.py",
    "release_integrity_validation.py",
}


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--phase", choices=("all", "source", "post-build"), default="all",
        help="Select all tests, tests that need only source, or tests that inspect built binaries.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    tests = sorted(TESTS.glob("*_validation.py"))
    if args.phase == "source":
        tests = [test for test in tests if test.name not in POST_BUILD_TESTS]
    elif args.phase == "post-build":
        tests = [test for test in tests if test.name in POST_BUILD_TESTS]

    version_test = TESTS / "version_consistency_validation.py"
    if args.phase != "post-build":
        if version_test not in tests:
            print(f"ERROR: missing {version_test.name}", file=sys.stderr)
            return 2
        tests.remove(version_test)
        tests.insert(0, version_test)
    if not tests:
        print(f"ERROR: no tests selected for phase {args.phase}", file=sys.stderr)
        return 2

    failed: list[str] = []
    for test in tests:
        print(f"==> {test.name}", flush=True)
        result = subprocess.run([sys.executable, "-B", "-X", "utf8", str(test)], cwd=ROOT)
        if result.returncode:
            failed.append(test.name)
    if failed:
        print("FAILED: " + ", ".join(failed), file=sys.stderr)
        return 1
    print(f"All {len(tests)} Python regression tests passed for phase {args.phase}.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
