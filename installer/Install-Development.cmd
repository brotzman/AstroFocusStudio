@echo off
setlocal EnableExtensions
cd /d "%~dp0"
title AstroFocus Studio 3.9.0 Setup

echo AstroFocus Studio 3.9.0 wird installiert.
echo Bitte bestaetigen Sie gegebenenfalls die Windows-Administratorabfrage.
echo.

"%~dp0AstroFocusSetup.exe" -AllowUnsignedDevelopment
set "rc=%ERRORLEVEL%"

if not "%rc%"=="0" (
    echo.
    echo FEHLER: Die Installation wurde mit Exitcode %rc% beendet.
    echo Diagnoseprotokoll: %ProgramData%\AstroFocusStudio\Logs\Installer.log
    echo.
    pause
    exit /b %rc%
)

echo.
echo Installation erfolgreich abgeschlossen.
timeout /t 3 /nobreak >nul
exit /b 0
