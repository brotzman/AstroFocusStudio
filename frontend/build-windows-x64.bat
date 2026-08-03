@echo off
setlocal
lld-link /nologo /machine:x64 /dll /noentry /def:kernel32.def /out:kernel32_stub.dll /implib:kernel32.lib || exit /b 1
if exist "kernel32_stub.dll" del /q "kernel32_stub.dll" >nul 2>&1
clang -target x86_64-pc-windows-msvc -c chkstk.s -o chkstk.obj || exit /b 1
clang-cl /nologo /W4 /WX /O2 /GS- /c ..\common\security_cookie.cpp /Fo:security_cookie.obj || exit /b 1
clang-cl /nologo /W4 /WX /O2 /GS- /c ..\common\security_entry.cpp /Fo:security_entry.obj || exit /b 1
clang-cl /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /c frontend.cpp /Fo:frontend.obj || exit /b 1
lld-link /nologo /machine:x64 /timestamp:0 /subsystem:windows /entry:WinMainCRTStartup /nodefaultlib frontend.obj security_cookie.obj security_entry.obj chkstk.obj app.res kernel32.lib user32.lib gdi32.lib msvcrt.lib /out:AstroFocusStudio.exe || exit /b 1
echo Erstellt: AstroFocusStudio.exe
endlocal
