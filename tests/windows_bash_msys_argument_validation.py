#!/usr/bin/env python3
"""Validate Git Bash/MSYS-safe LLVM switches and native Windows paths."""
from __future__ import annotations

import os
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BUILD = ROOT / "build-windows-x64.sh"
text = BUILD.read_text(encoding="utf-8")

# Git for Windows path conversion treats arguments such as /nologo as POSIX
# paths and can rewrite them to C:/Program Files/Git/nologo. Native LLVM tools
# accept equivalent dash-prefixed options. Conversely, paths embedded in
# options such as -Fo:/d/a/... are not converted by MSYS and must be converted
# explicitly with cygpath before they reach clang-cl or lld-link.
native_lines = [
    line.strip()
    for line in text.splitlines()
    if '"$CLANG"' in line
    or '"$CLANG_CL"' in line
    or '"$LLD_LINK"' in line
    or "local args=(" in line
    or "args+=(" in line
]
joined = "\n".join(native_lines)

slash_switch = re.compile(r"(?<![A-Za-z0-9_])/[A-Za-z][A-Za-z0-9_-]*(?::|\b)")
violations = sorted(set(slash_switch.findall(joined)))
raw_embedded_path = re.compile(r'"-(?:Fo|def|out|implib):\$(?:ROOT|OUT_DIR|BIN_DIR|OBJ_ROOT|GEN_DIR|obj_dir|lib_dir|source_dir)')
raw_path_violations = raw_embedded_path.findall(text)


def write_executable(path: Path, body: str) -> None:
    path.write_text("#!/usr/bin/env bash\nset -euo pipefail\n" + body, encoding="utf-8")
    path.chmod(0o755)


def _is_working_gnu_bash(candidate: Path) -> bool:
    """Accept GNU Bash itself, but reject the Windows WSL launcher."""
    if not candidate.is_file():
        return False
    normalized = candidate.as_posix().lower()
    if normalized.endswith("/windows/system32/bash.exe") or "/windowsapps/" in normalized:
        return False
    try:
        probe = subprocess.run(
            [str(candidate), "--version"],
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            timeout=10,
            check=False,
        )
    except (OSError, subprocess.SubprocessError):
        return False
    return probe.returncode == 0 and "gnu bash" in probe.stdout.lower()


def resolve_test_bash() -> tuple[Path | None, str]:
    """Resolve Git for Windows Bash explicitly instead of accidentally launching WSL."""
    candidates: list[Path] = []

    def add(value: str | os.PathLike[str] | None) -> None:
        if not value:
            return
        path = Path(value).expanduser()
        if path not in candidates:
            candidates.append(path)

    for variable in ("ASTROFOCUS_GIT_BASH", "GIT_BASH_EXE"):
        add(os.environ.get(variable))

    if os.name == "nt":
        for variable in ("ProgramFiles", "ProgramW6432", "ProgramFiles(x86)"):
            base = os.environ.get(variable)
            if base:
                add(Path(base) / "Git" / "bin" / "bash.exe")
                add(Path(base) / "Git" / "usr" / "bin" / "bash.exe")
        local_app_data = os.environ.get("LOCALAPPDATA")
        if local_app_data:
            add(Path(local_app_data) / "Programs" / "Git" / "bin" / "bash.exe")
            add(Path(local_app_data) / "Programs" / "Git" / "usr" / "bin" / "bash.exe")

        git = shutil.which("git")
        if git:
            git_path = Path(git)
            # Normal Git for Windows PATH entry: <root>/cmd/git.exe.
            add(git_path.parent.parent / "bin" / "bash.exe")
            add(git_path.parent.parent / "usr" / "bin" / "bash.exe")
            try:
                probe = subprocess.run(
                    [git, "--exec-path"],
                    text=True,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.DEVNULL,
                    timeout=10,
                    check=False,
                )
                if probe.returncode == 0 and probe.stdout.strip():
                    exec_path = Path(probe.stdout.strip())
                    for parent in (exec_path, *exec_path.parents):
                        if parent.name.lower() == "git":
                            add(parent / "bin" / "bash.exe")
                            add(parent / "usr" / "bin" / "bash.exe")
                            break
            except (OSError, subprocess.SubprocessError):
                pass
    else:
        add(shutil.which("bash"))

    # PATH is a last resort. On Windows this may be System32\bash.exe (WSL),
    # which _is_working_gnu_bash deliberately rejects.
    add(shutil.which("bash"))

    rejected: list[str] = []
    for candidate in candidates:
        if _is_working_gnu_bash(candidate):
            return candidate, f"using {candidate}"
        if candidate.exists():
            rejected.append(str(candidate))
    detail = "Git Bash not found"
    if rejected:
        detail += f"; rejected non-GNU/WSL launcher(s): {', '.join(rejected)}"
    return None, detail


def run_msys_simulation() -> tuple[bool, str]:
    """Run the frontend build with fake native tools and a fake MINGW shell."""
    bash, bash_detail = resolve_test_bash()
    if bash is None:
        return False, bash_detail

    with tempfile.TemporaryDirectory(prefix="afs-msys-test-") as tmp:
        temp = Path(tmp)
        fake_bin = temp / "bin"
        fake_bin.mkdir()
        log = temp / "native-tools.log"
        out_dir = temp / "out"

        write_executable(fake_bin / "uname", "printf '%s\\n' 'MINGW64_NT-10.0-22631'\n")
        write_executable(
            fake_bin / "cygpath",
            """path="${@: -1}"
printf 'C:/mock%s\\n' "$path"
""",
        )
        logger = """{
  printf '%s' "$(basename "$0")"
  for arg in "$@"; do printf '\\t%s' "$arg"; done
  printf '\\n'
} >> "$ASTROFOCUS_FAKE_TOOL_LOG"
"""
        for tool in ("clang", "clang-cl", "lld-link"):
            write_executable(fake_bin / tool, logger)

        env = os.environ.copy()
        env.update(
            {
                "PATH": str(fake_bin) + os.pathsep + env.get("PATH", ""),
                "OUT_DIR": str(out_dir),
                "ASTROFOCUS_FAKE_TOOL_LOG": str(log),
                "CLANG": "clang",
                "CLANG_CL": "clang-cl",
                "LLD_LINK": "lld-link",
                # Use the interpreter executing this test. Git Bash can launch the
                # mixed-form path, and MSYS converts its following file arguments.
                "PYTHON": Path(sys.executable).as_posix(),
            }
        )
        result = subprocess.run(
            [str(bash), str(BUILD), "--clean", "--component", "frontend"],
            cwd=ROOT,
            env=env,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            check=False,
        )
        if result.returncode != 0:
            return False, (
                f"simulated build failed ({result.returncode}; {bash_detail}): "
                f"{result.stdout.strip()}"
            )
        if not log.exists():
            return False, "simulated native tools produced no argument log"

        lines = [line for line in log.read_text(encoding="utf-8").splitlines() if line.strip()]
        args = [arg for line in lines for arg in line.split("\t")[1:]]
        bad_git_path = [arg for arg in args if "Program Files/Git" in arg]
        raw_posix_paths = [arg for arg in args if arg.startswith("/") or ":/mnt/" in arg]
        embedded_outputs = [arg for arg in args if arg.startswith(("-Fo:", "-def:", "-out:", "-implib:"))]
        bad_embedded_outputs = [arg for arg in embedded_outputs if not arg.split(":", 1)[1].startswith("C:/mock/")]
        native_inputs = [
            arg
            for arg in args
            if arg.endswith((".cpp", ".s", ".obj", ".res", ".lib"))
            and not arg.startswith(("-Fo:", "-def:", "-out:", "-implib:"))
        ]
        bad_native_inputs = [arg for arg in native_inputs if not arg.startswith("C:/mock/")]

        problems: list[str] = []
        if bad_git_path:
            problems.append(f"Git installation path rewrite observed: {bad_git_path}")
        if raw_posix_paths:
            problems.append(f"raw POSIX paths reached native tools: {raw_posix_paths}")
        if not embedded_outputs:
            problems.append("no embedded output/import paths were logged")
        if bad_embedded_outputs:
            problems.append(f"embedded paths were not converted: {bad_embedded_outputs}")
        if not native_inputs:
            problems.append("no native source/object/resource inputs were logged")
        if bad_native_inputs:
            problems.append(f"native input paths were not converted: {bad_native_inputs}")
        success_detail = f"{len(lines)} native tool invocations checked; {bash_detail}"
        return not problems, "; ".join(problems) if problems else success_detail


simulation_ok, simulation_detail = run_msys_simulation()
checks = {
    "central Bash build invokes clang-cl": '"$CLANG_CL"' in text,
    "central Bash build invokes lld-link": '"$LLD_LINK"' in text,
    "clang-cl uses MSYS-safe -nologo": '"$CLANG_CL" -nologo' in text,
    "lld-link uses MSYS-safe -nologo": '"$LLD_LINK" -nologo' in text,
    "link argument array uses dash-prefixed COFF options": "local args=(-nologo -machine:x64" in text,
    "Windows POSIX shells are detected": "MINGW*|MSYS*|CYGWIN*" in text,
    "native paths use mixed-form cygpath conversion": 'cygpath -am "$path"' in text,
    "no MSVC-style slash switch reaches native LLVM from Bash": not violations,
    "no raw POSIX path is embedded in LLVM output options": not raw_path_violations,
    "no global path-conversion disable masks path bugs": "MSYS2_ARG_CONV_EXCL=*" not in text and "MSYS_NO_PATHCONV=1" not in text,
    "Windows test resolver searches Git for Windows explicitly": 'Path(base) / "Git" / "bin" / "bash.exe"' in Path(__file__).read_text(encoding="utf-8"),
    "Windows test resolver rejects WSL and WindowsApps launchers": 'windows/system32/bash.exe' in Path(__file__).read_text(encoding="utf-8") and '"/windowsapps/"' in Path(__file__).read_text(encoding="utf-8"),
    "simulated Git Bash build passes Windows paths to native LLVM": simulation_ok,
}

for name, ok in checks.items():
    detail = ""
    if name.startswith("no MSVC") and violations:
        detail = f" ({', '.join(violations)})"
    elif name.startswith("no raw POSIX") and raw_path_violations:
        detail = f" ({', '.join(raw_path_violations)})"
    elif name.startswith("simulated"):
        detail = f" ({simulation_detail})"
    print(f'{name}: {"PASS" if ok else "FAIL"}{detail}')
print(f"SUMMARY {sum(checks.values())}/{len(checks)}")
raise SystemExit(0 if all(checks.values()) else 1)
