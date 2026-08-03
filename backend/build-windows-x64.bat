@echo off
setlocal EnableExtensions
where bash.exe >nul 2>&1 || exit /b 2
bash.exe "%~dp0..\build-windows-x64.sh" --component backend
exit /b %ERRORLEVEL%
