@echo off
setlocal EnableExtensions
where bash.exe >nul 2>&1 || (
  echo FEHLER: bash.exe wurde nicht gefunden. Git for Windows ist fuer den reproduzierbaren Build erforderlich.
  exit /b 2
)
bash.exe "%~dp0build-windows-x64.sh" --clean
exit /b %ERRORLEVEL%
