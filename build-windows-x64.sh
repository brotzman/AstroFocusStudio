#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")" && pwd)"
CLANG=${CLANG:-clang}
CLANG_CL=${CLANG_CL:-clang-cl}
LLD_LINK=${LLD_LINK:-lld-link}
regen_import_libs(){
  local dir=$1; shift
  cd "$ROOT/$dir"
  for def in "$@"; do
    "$LLD_LINK" /nologo /machine:x64 /dll /noentry "/def:${def}.def" "/out:${def}_stub.dll" "/implib:${def}.lib"
    rm -f "${def}_stub.dll"
  done
}
build_one(){
  local dir=$1 source=$2 object=$3 output=$4 libs=$5
  cd "$ROOT/$dir"
  "$CLANG" -target x86_64-pc-windows-msvc -c chkstk.s -o chkstk.obj
  "$CLANG_CL" /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /c "$source" "/Fo:$object"
  "$CLANG_CL" /nologo /W4 /WX /O2 /GS- /c "$ROOT/common/security_cookie.cpp" /Fo:security_cookie.obj
  "$CLANG_CL" /nologo /W4 /WX /O2 /GS- /c "$ROOT/common/security_entry.cpp" /Fo:security_entry.obj
  # shellcheck disable=SC2086
  "$LLD_LINK" /nologo /machine:x64 /timestamp:0 /subsystem:windows /entry:WinMainCRTStartup /nodefaultlib "$object" security_cookie.obj security_entry.obj chkstk.obj app.res $libs "/out:$output"
}
regen_import_libs frontend kernel32
regen_import_libs backend kernel32
regen_import_libs focuser_setup kernel32
build_one frontend frontend.cpp frontend.obj AstroFocusStudio.exe "kernel32.lib user32.lib gdi32.lib msvcrt.lib"
build_one backend backend.cpp backend.obj AstroFocusEngine.exe "kernel32.lib user32.lib gdi32.lib ole32.lib oleaut32.lib msvcrt.lib kernel_extra.lib user_extra.lib"
build_one focuser_setup focuser_setup.cpp focuser_setup.obj AstroFocusFocuserSetup.exe "kernel32.lib user32.lib ole32.lib oleaut32.lib msvcrt.lib"
"$ROOT/device_host/build-windows-x64.sh"
"$ROOT/tools/build-windows-x64.sh"
echo "Windows-x64-Build 3.9.0 abgeschlossen."
