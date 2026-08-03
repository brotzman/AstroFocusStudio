#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")" && pwd)"
OUT_DIR="${OUT_DIR:-$ROOT/out/windows-x64}"
BIN_DIR="$OUT_DIR/bin"
OBJ_ROOT="$OUT_DIR/obj"
GEN_DIR="$OUT_DIR/generated"
CLANG="${CLANG:-clang}"
CLANG_CL="${CLANG_CL:-clang-cl}"
LLD_LINK="${LLD_LINK:-lld-link}"
PYTHON="${PYTHON:-python3}"
RUN_TESTS=0
CLEAN=0
RELEASE=0
COMPONENT="all"

usage(){
  cat <<EOF
Usage: ./build-windows-x64.sh [--clean] [--test] [--release] [--component NAME]
Components: frontend, backend, focuser_setup, device_host, tools, all
Outputs: $OUT_DIR
EOF
}

while (($#)); do
  case "$1" in
    --clean) CLEAN=1 ;;
    --test) RUN_TESTS=1 ;;
    --release) RELEASE=1 ;;
    --component) shift; COMPONENT="${1:-}" ;;
    -h|--help) usage; exit 0 ;;
    *) echo "Unknown argument: $1" >&2; usage >&2; exit 2 ;;
  esac
  shift
done

case "$COMPONENT" in frontend|backend|focuser_setup|device_host|tools|all) ;; *) echo "Unknown component: $COMPONENT" >&2; exit 2;; esac

for tool in "$CLANG" "$CLANG_CL" "$LLD_LINK" "$PYTHON"; do
  command -v "$tool" >/dev/null 2>&1 || { echo "Required tool not found: $tool" >&2; exit 2; }
done

if ((CLEAN)); then rm -rf "$OUT_DIR"; fi
mkdir -p "$BIN_DIR" "$OBJ_ROOT" "$GEN_DIR"
VERSION="$(tr -d '\r\n' < "$ROOT/VERSION")"
"$PYTHON" -B "$ROOT/tools/generate_version.py" --version-file "$ROOT/VERSION" --header "$ROOT/common/version.h"

make_import_lib(){
  local component="$1" name="$2" source_dir="$3"
  local obj_dir="$OBJ_ROOT/$component" lib_dir="$obj_dir/lib"
  mkdir -p "$lib_dir"
  "$LLD_LINK" /nologo /machine:x64 /dll /noentry "/def:$source_dir/$name.def" "/out:$lib_dir/${name}_stub.dll" "/implib:$lib_dir/$name.lib"
  rm -f "$lib_dir/${name}_stub.dll"
}

make_resources(){
  local component="$1" exe="$2" description="$3"
  local res="$GEN_DIR/$component/app.res"
  mkdir -p "$(dirname "$res")"
  "$PYTHON" -B "$ROOT/tools/generate_windows_resources.py" \
    --icon "$ROOT/assets/AstroFocusStudio.ico" \
    --version-file "$ROOT/VERSION" \
    --output "$res" --exe "$exe" --description "$description"
  printf '%s' "$res"
}

compile_common(){
  local component="$1" source_dir="$2"
  local obj_dir="$OBJ_ROOT/$component"
  mkdir -p "$obj_dir"
  "$CLANG" -target x86_64-pc-windows-msvc -c "$source_dir/chkstk.s" -o "$obj_dir/chkstk.obj"
  "$CLANG_CL" /nologo /W4 /WX /O2 /GS- /c "$ROOT/common/security_cookie.cpp" "/Fo:$obj_dir/security_cookie.obj"
  "$CLANG_CL" /nologo /W4 /WX /O2 /GS- /c "$ROOT/common/security_entry.cpp" "/Fo:$obj_dir/security_entry.obj"
}

link_app(){
  local component="$1" exe="$2" object="$3" res="$4"; shift 4
  local obj_dir="$OBJ_ROOT/$component" lib_dir="$obj_dir/lib"
  local args=(/nologo /machine:x64 /timestamp:0 /subsystem:windows /entry:WinMainCRTStartup /nodefaultlib
    "$object" "$obj_dir/security_cookie.obj" "$obj_dir/security_entry.obj" "$obj_dir/chkstk.obj" "$res")
  local lib
  for lib in "$@"; do args+=("$lib_dir/$lib.lib"); done
  args+=("/out:$BIN_DIR/$exe")
  "$LLD_LINK" "${args[@]}"
}

build_frontend(){
  local component=frontend source_dir="$ROOT/frontend" obj_dir="$OBJ_ROOT/frontend"
  for lib in kernel32 user32 gdi32 msvcrt; do make_import_lib "$component" "$lib" "$source_dir"; done
  compile_common "$component" "$source_dir"
  "$CLANG_CL" /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /c "$source_dir/frontend.cpp" "/Fo:$obj_dir/frontend.obj"
  local res; res="$(make_resources "$component" AstroFocusStudio.exe 'AstroFocus Studio user interface')"
  link_app "$component" AstroFocusStudio.exe "$obj_dir/frontend.obj" "$res" kernel32 user32 gdi32 msvcrt
}

build_backend(){
  local component=backend source_dir="$ROOT/backend" obj_dir="$OBJ_ROOT/backend"
  for lib in kernel32 user32 gdi32 ole32 oleaut32 msvcrt kernel_extra user_extra; do make_import_lib "$component" "$lib" "$source_dir"; done
  compile_common "$component" "$source_dir"
  "$CLANG_CL" /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /c "$source_dir/backend.cpp" "/Fo:$obj_dir/backend.obj"
  local res; res="$(make_resources "$component" AstroFocusEngine.exe 'AstroFocus Studio focus engine')"
  link_app "$component" AstroFocusEngine.exe "$obj_dir/backend.obj" "$res" kernel32 user32 gdi32 ole32 oleaut32 msvcrt kernel_extra user_extra
}

build_focuser_setup(){
  local component=focuser_setup source_dir="$ROOT/focuser_setup" obj_dir="$OBJ_ROOT/focuser_setup"
  for lib in kernel32 user32 ole32 oleaut32 msvcrt; do make_import_lib "$component" "$lib" "$source_dir"; done
  compile_common "$component" "$source_dir"
  "$CLANG_CL" /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /c "$source_dir/focuser_setup.cpp" "/Fo:$obj_dir/focuser_setup.obj"
  local res; res="$(make_resources "$component" AstroFocusFocuserSetup.exe 'AstroFocus Studio focuser setup')"
  link_app "$component" AstroFocusFocuserSetup.exe "$obj_dir/focuser_setup.obj" "$res" kernel32 user32 ole32 oleaut32 msvcrt
}

build_device_host(){
  local component=device_host source_dir="$ROOT/device_host" obj_dir="$OBJ_ROOT/device_host"
  for lib in kernel32 ole32 oleaut32; do make_import_lib "$component" "$lib" "$source_dir"; done
  compile_common "$component" "$source_dir"
  local res_camera res_focuser
  res_camera="$(make_resources camera_host AstroFocusCameraHost.exe 'AstroFocus Studio camera host')"
  res_focuser="$(make_resources focuser_host AstroFocusFocuserHost.exe 'AstroFocus Studio focuser host')"
  "$CLANG_CL" /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /DASTROFOCUS_HOST_CAMERA=1 /c "$source_dir/device_host.cpp" "/Fo:$obj_dir/camera_host.obj"
  link_app "$component" AstroFocusCameraHost.exe "$obj_dir/camera_host.obj" "$res_camera" kernel32 ole32 oleaut32
  "$CLANG_CL" /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /DASTROFOCUS_HOST_CAMERA=0 /c "$source_dir/device_host.cpp" "/Fo:$obj_dir/focuser_host.obj"
  link_app "$component" AstroFocusFocuserHost.exe "$obj_dir/focuser_host.obj" "$res_focuser" kernel32 ole32 oleaut32
}

build_tools(){
  local component=tools source_dir="$ROOT/tools" obj_dir="$OBJ_ROOT/tools"
  for lib in kernel32 user32; do make_import_lib "$component" "$lib" "$source_dir"; done
  compile_common "$component" "$source_dir"
  local res_updater res_setup
  res_updater="$(make_resources updater AstroFocusUpdater.exe 'AstroFocus Studio updater')"
  res_setup="$(make_resources setup AstroFocusSetup.exe 'AstroFocus Studio setup launcher')"
  "$CLANG_CL" /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /c "$source_dir/updater_launcher.cpp" "/Fo:$obj_dir/updater_launcher.obj"
  link_app "$component" AstroFocusUpdater.exe "$obj_dir/updater_launcher.obj" "$res_updater" kernel32 user32
  "$CLANG_CL" /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /c "$source_dir/setup_launcher.cpp" "/Fo:$obj_dir/setup_launcher.obj"
  link_app "$component" AstroFocusSetup.exe "$obj_dir/setup_launcher.obj" "$res_setup" kernel32 user32
}

case "$COMPONENT" in
  frontend) build_frontend ;;
  backend) build_backend ;;
  focuser_setup) build_focuser_setup ;;
  device_host) build_device_host ;;
  tools) build_tools ;;
  all) build_frontend; build_backend; build_focuser_setup; build_device_host; build_tools ;;
esac

if ((RELEASE)); then
  rm -rf "$ROOT/dist/windows-x64"
  mkdir -p "$ROOT/dist/windows-x64"
  cp -f "$BIN_DIR"/*.exe "$ROOT/dist/windows-x64/"
fi

if ((RUN_TESTS)); then
  "$PYTHON" -B "$ROOT/scripts/run_python_tests.py"
  CXX="${CXX:-clang++}" "$ROOT/scripts/Run-NativeTests.sh"
fi

echo "Windows-x64 build $VERSION completed: $BIN_DIR"
