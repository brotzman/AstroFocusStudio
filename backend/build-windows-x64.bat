@echo off
setlocal
clang -target x86_64-pc-windows-msvc -c chkstk.s -o chkstk.obj || exit /b 1
clang-cl /nologo /W4 /WX /O2 /GS- /c ..\common\security_cookie.cpp /Fo:security_cookie.obj || exit /b 1
clang-cl /nologo /W4 /WX /O2 /GS- /c ..\common\security_entry.cpp /Fo:security_entry.obj || exit /b 1
clang-cl /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /c backend.cpp /Fo:backend.obj || exit /b 1
lld-link /nologo /machine:x64 /timestamp:0 /subsystem:windows /entry:WinMainCRTStartup /nodefaultlib backend.obj security_cookie.obj security_entry.obj chkstk.obj app.res kernel32.lib user32.lib gdi32.lib ole32.lib oleaut32.lib msvcrt.lib kernel_extra.lib user_extra.lib /out:AstroFocusEngine.exe || exit /b 1
echo Erstellt: AstroFocusEngine.exe
endlocal
