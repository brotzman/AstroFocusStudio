@echo off
setlocal
cd /d "%~dp0"

where py >nul 2>&1
if not errorlevel 1 (
  py -3 -X utf8 scripts\remove_legacy_version_files.py --root .
) else (
  python -X utf8 scripts\remove_legacy_version_files.py --root .
)

if errorlevel 1 (
  echo.
  echo Die Versionsbereinigung ist fehlgeschlagen.
  pause
  exit /b 1
)

echo.
echo Die bekannten Altdateien wurden entfernt. Bitte jetzt ausfuehren:
echo   git add -A
echo   git commit -m "Remove superseded version files"
echo   git push
pause
exit /b 0
