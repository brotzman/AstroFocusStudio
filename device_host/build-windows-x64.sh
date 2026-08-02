#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")" && pwd)"
cd "$ROOT"
for def in kernel32 ole32 oleaut32; do
  lld-link /nologo /machine:x64 /dll /noentry "/def:${def}.def" "/out:${def}_stub.dll" "/implib:${def}.lib"
  rm -f "${def}_stub.dll"
done
clang -target x86_64-pc-windows-msvc -c chkstk.s -o chkstk.obj
clang-cl /nologo /W4 /WX /O2 /GS- /c ../common/security_cookie.cpp /Fo:security_cookie.obj
clang-cl /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /DASTROFOCUS_HOST_CAMERA=1 /c device_host.cpp /Fo:camera_host.obj
lld-link /nologo /machine:x64 /timestamp:0 /subsystem:windows /entry:WinMainCRTStartup /nodefaultlib camera_host.obj security_cookie.obj chkstk.obj kernel32.lib ole32.lib oleaut32.lib /out:AstroFocusCameraHost.exe
clang-cl /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /DASTROFOCUS_HOST_CAMERA=0 /c device_host.cpp /Fo:focuser_host.obj
lld-link /nologo /machine:x64 /timestamp:0 /subsystem:windows /entry:WinMainCRTStartup /nodefaultlib focuser_host.obj security_cookie.obj chkstk.obj kernel32.lib ole32.lib oleaut32.lib /out:AstroFocusFocuserHost.exe
printf 'Device hosts 3.8.8 built.\n'
