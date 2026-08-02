@echo off
setlocal
for %%D in (kernel32 ole32 oleaut32) do (
  lld-link /nologo /machine:x64 /dll /noentry /def:%%D.def /out:%%D_stub.dll /implib:%%D.lib || exit /b 1
  del /q %%D_stub.dll
)
clang -target x86_64-pc-windows-msvc -c chkstk.s -o chkstk.obj || exit /b 1
clang-cl /nologo /W4 /WX /O2 /GS- /c ..\common\security_cookie.cpp /Fo:security_cookie.obj || exit /b 1
clang-cl /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /DASTROFOCUS_HOST_CAMERA=1 /c device_host.cpp /Fo:camera_host.obj || exit /b 1
lld-link /nologo /machine:x64 /timestamp:0 /subsystem:windows /entry:WinMainCRTStartup /nodefaultlib camera_host.obj security_cookie.obj chkstk.obj kernel32.lib ole32.lib oleaut32.lib /out:AstroFocusCameraHost.exe || exit /b 1
clang-cl /nologo /W4 /WX /O2 /GS /DUNICODE /D_UNICODE /DASTROFOCUS_HOST_CAMERA=0 /c device_host.cpp /Fo:focuser_host.obj || exit /b 1
lld-link /nologo /machine:x64 /timestamp:0 /subsystem:windows /entry:WinMainCRTStartup /nodefaultlib focuser_host.obj security_cookie.obj chkstk.obj kernel32.lib ole32.lib oleaut32.lib /out:AstroFocusFocuserHost.exe || exit /b 1
endlocal
