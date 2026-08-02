@echo off
setlocal
lld-link /nologo /machine:x64 /dll /noentry /def:kernel32.def /out:kernel32_stub.dll /implib:kernel32.lib || exit /b 1
lld-link /nologo /machine:x64 /dll /noentry /def:user32.def /out:user32_stub.dll /implib:user32.lib || exit /b 1
if exist "kernel32_stub.dll" del /q "kernel32_stub.dll" >nul 2>&1
if exist "user32_stub.dll" del /q "user32_stub.dll" >nul 2>&1
clang -target x86_64-pc-windows-msvc -c chkstk.s -o chkstk.obj || exit /b 1
clang-cl /nologo /W4 /WX /O2 /GS- /c ..\common\security_cookie.cpp /Fo:security_cookie.obj || exit /b 1
clang-cl /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /c updater_launcher.cpp /Fo:updater_launcher.obj || exit /b 1
lld-link /nologo /machine:x64 /timestamp:0 /subsystem:windows /entry:WinMainCRTStartup /nodefaultlib updater_launcher.obj security_cookie.obj chkstk.obj kernel32.lib user32.lib /out:AstroFocusUpdater.exe || exit /b 1
clang-cl /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /c setup_launcher.cpp /Fo:setup_launcher.obj || exit /b 1
lld-link /nologo /machine:x64 /timestamp:0 /subsystem:windows /entry:WinMainCRTStartup /nodefaultlib setup_launcher.obj security_cookie.obj chkstk.obj kernel32.lib user32.lib /out:AstroFocusSetup.exe || exit /b 1
endlocal
