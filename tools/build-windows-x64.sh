#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
lld-link /nologo /machine:x64 /dll /noentry /def:kernel32.def /out:kernel32_stub.dll /implib:kernel32.lib
lld-link /nologo /machine:x64 /dll /noentry /def:user32.def /out:user32_stub.dll /implib:user32.lib
rm -f kernel32_stub.dll user32_stub.dll
clang -target x86_64-pc-windows-msvc -c chkstk.s -o chkstk.obj
clang-cl /nologo /W4 /WX /O2 /GS- /c ../common/security_cookie.cpp /Fo:security_cookie.obj
clang-cl /nologo /W4 /WX /O2 /GS- /c ../common/security_entry.cpp /Fo:security_entry.obj
clang-cl /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /c updater_launcher.cpp /Fo:updater_launcher.obj
lld-link /nologo /machine:x64 /timestamp:0 /subsystem:windows /entry:WinMainCRTStartup /nodefaultlib updater_launcher.obj security_cookie.obj security_entry.obj chkstk.obj kernel32.lib user32.lib /out:AstroFocusUpdater.exe
clang-cl /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /c setup_launcher.cpp /Fo:setup_launcher.obj
lld-link /nologo /machine:x64 /timestamp:0 /subsystem:windows /entry:WinMainCRTStartup /nodefaultlib setup_launcher.obj security_cookie.obj security_entry.obj chkstk.obj kernel32.lib user32.lib /out:AstroFocusSetup.exe
printf 'Updater/setup launchers 3.9.0 built.\n'
