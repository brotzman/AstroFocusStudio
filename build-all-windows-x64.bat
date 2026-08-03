@echo off
setlocal

call :build frontend || exit /b 1
call :build backend || exit /b 1
call :build focuser_setup || exit /b 1
call :build device_host || exit /b 1
call :build tools || exit /b 1

echo.
echo AstroFocus Studio 3.9.0 wurde vollständig erstellt: 7 Windows-x64-Programme.
exit /b 0

:build
pushd "%~1" || exit /b 1
call build-windows-x64.bat
set "BUILD_RESULT=%ERRORLEVEL%"
popd
exit /b %BUILD_RESULT%
