#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BUILD_DIR="${RUNNER_TEMP:-$ROOT/.native-test-build}/astrofocus-native-tests"
CXX="${CXX:-clang++-18}"

if ! command -v "$CXX" >/dev/null 2>&1; then
    echo "ERROR: C++ compiler '$CXX' was not found." >&2
    echo "PATH=$PATH" >&2
    exit 2
fi

COMPILER_PATH="$(command -v "$CXX")"
COMPILER_VERSION="$($COMPILER_PATH --version 2>&1 | head -n 1)"
echo "Native test compiler: $COMPILER_PATH"
echo "Native test compiler version: $COMPILER_VERSION"

SANITIZER_LINK_FLAGS=()
if "$COMPILER_PATH" --version 2>&1 | grep -qi clang; then
    # Embed compiler-rt's sanitizer runtimes so a runner image cannot fail
    # with exit 127 merely because a shared ASan/UBSan library is absent.
    SANITIZER_LINK_FLAGS+=( -static-libsan )
elif "$COMPILER_PATH" --version 2>&1 | grep -Eqi 'gcc|g\+\+'; then
    SANITIZER_LINK_FLAGS+=( -static-libasan -static-libubsan )
fi

SYMBOLIZER=""
for candidate in llvm-symbolizer-18 llvm-symbolizer-17 llvm-symbolizer-16 llvm-symbolizer; do
    if command -v "$candidate" >/dev/null 2>&1; then
        SYMBOLIZER="$(command -v "$candidate")"
        break
    fi
done
if [[ -n "$SYMBOLIZER" ]]; then
    export ASAN_SYMBOLIZER_PATH="$SYMBOLIZER"
    echo "ASan symbolizer: $ASAN_SYMBOLIZER_PATH"
else
    echo "ASan symbolizer: not found; tests remain functional without symbolized stacks"
fi

rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"

print_binary_diagnostics() {
    local binary="$1"
    echo "--- binary diagnostics: $binary ---" >&2
    if command -v file >/dev/null 2>&1; then file "$binary" >&2 || true; fi
    if command -v ldd >/dev/null 2>&1; then ldd "$binary" >&2 || true; fi
    ls -l "$binary" >&2 || true
    echo "-------------------------------------" >&2
}

compile_and_run() {
    local source="$1"
    local output="$2"
    local binary="$BUILD_DIR/$output"
    echo "==> ${source##*/}"
    "$COMPILER_PATH" \
        -std=c++17 -O1 -g -fno-omit-frame-pointer \
        -ffunction-sections -fdata-sections \
        -fsanitize=address,undefined \
        -Wno-ignored-attributes \
        "$ROOT/$source" \
        -Wl,--gc-sections \
        "${SANITIZER_LINK_FLAGS[@]}" \
        -o "$binary"

    if [[ ! -f "$binary" ]]; then
        echo "ERROR: compiler returned successfully but did not create $binary" >&2
        exit 3
    fi
    if [[ ! -x "$binary" ]]; then
        chmod u+x "$binary"
    fi

    set +e
    ASAN_OPTIONS="detect_leaks=1:halt_on_error=1:strict_string_checks=1" \
    UBSAN_OPTIONS="halt_on_error=1:print_stacktrace=1" \
        "$binary"
    local rc=$?
    set -e
    if [[ $rc -ne 0 ]]; then
        echo "ERROR: native test '$output' exited with code $rc." >&2
        print_binary_diagnostics "$binary"
        exit "$rc"
    fi
}

compile_and_run tests/command_line_args_validation_388.cpp command_line_args_validation_388
compile_and_run tests/frontend_logic_validation_388.cpp frontend_logic_validation_388
compile_and_run tests/actual_backend_validation_388.cpp actual_backend_validation_388

echo "Alle nativen ASan-/UBSan-Tests wurden bestanden."
