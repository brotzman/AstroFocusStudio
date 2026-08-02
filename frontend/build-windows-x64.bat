@echo off
setlocal
clang -target x86_64-pc-windows-msvc -c chkstk.s -o chkstk.obj || exit /b 1
clang-cl /nologo /W4 /WX /O2 /GS- /c ..\common\security_cookie.cpp /Fo:security_cookie.obj || exit /b 1
clang-cl /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /c frontend.cpp /Fo:frontend.obj || exit /b 1
lld-link /nologo /machine:x64 /timestamp:0 /subsystem:windows /entry:WinMainCRTStartup /nodefaultlib frontend.obj security_cookie.obj chkstk.obj app.res kernel32.lib user32.lib gdi32.lib msvcrt.lib /out:AstroFocusStudio.exe || exit /b 1
echo Erstellt: AstroFocusStudio.exe
endlocal
