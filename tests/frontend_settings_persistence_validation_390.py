from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
FRONTEND = (ROOT / "frontend" / "frontend.cpp").read_text(encoding="utf-8")
KERNEL_DEF = (ROOT / "frontend" / "kernel32.def").read_text(encoding="utf-8")
NATIVE = (ROOT / "tests" / "frontend_logic_validation_390.cpp").read_text(encoding="utf-8")
WORKFLOW = (ROOT / ".github" / "workflows" / "windows-build.yml").read_text(encoding="utf-8")

checks: list[tuple[str, bool]] = []

def check(name: str, condition: bool) -> None:
    checks.append((name, bool(condition)))

save_body = FRONTEND.split("static BOOL SaveThemeSetting(){", 1)[1].split("static void LoadThemeSetting(){", 1)[0]
load_body = FRONTEND.split("static void LoadThemeSetting(){", 1)[1].split("static void SetControlThemeWith", 1)[0]
refresh_body = FRONTEND.split("static void RefreshTheme(BOOL persist){", 1)[1].split("static void AppendFrontendTrace", 1)[0]

check("theme settings use a dedicated per-user path helper", "static BOOL BuildUserDataFilePath" in FRONTEND)
check("theme settings prefer LOCALAPPDATA", 'GetEnvironmentVariableW(L"LOCALAPPDATA"' in FRONTEND)
check("theme settings live below the AstroFocusStudio user directory", 'AppendWideBounded(dir,700,L"\\\\AstroFocusStudio")' in FRONTEND)
check("theme settings have a writable TEMP fallback", 'GetTempPathW(520,root)' in FRONTEND and 'AppendWideBounded(dir,700,L"AstroFocusStudio")' in FRONTEND)
check("theme save no longer writes into the installation directory", "BuildPath(" not in save_body)
check("theme load checks the per-user file first", 'BuildUserDataFilePath(L"AstroFocusUiSettings.ini"' in load_body)
check("legacy installation-directory settings are read only for migration", 'BuildPath(L"AstroFocusUiSettings.ini",legacyPath)' in load_body and '(void)SaveThemeSetting()' in load_body)
check("theme save writes to a process-specific temporary file", 'L".tmp.%u"' in save_body and "GetCurrentProcessId()" in save_body)
check("theme save flushes data before publication", "FlushFileBuffers(f)" in save_body)
check("theme save publishes atomically", "MoveFileExW(tempPath,g_themeSettingsPath" in save_body)
check("atomic replacement uses replace-existing and write-through flags", "MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH" in save_body)
check("a failed save removes only the temporary file", "if(!ok)DeleteFileW(tempPath)" in save_body and "DeleteFileW(g_themeSettingsPath)" not in save_body)
check("theme persistence failure is logged with path and Windows error", "theme settings save failed error=%lu path=%s" in refresh_body)
check("theme persistence failure no longer opens the modal warning dialog", "Das Farbschema wurde für diese Sitzung" not in FRONTEND)
check("frontend imports atomic persistence APIs", all(name in KERNEL_DEF for name in ("FlushFileBuffers", "MoveFileExW")))
check("native frontend harness provides atomic persistence stubs", "FlushFileBuffers" in NATIVE and "MoveFileExW" in NATIVE)
check("GitHub preflight requires the settings persistence regression", "tests\\frontend_settings_persistence_validation_390.py" in WORKFLOW)

# Guard against accidental direct overwrite of the final settings file.
direct_final_overwrite = re.search(
    r"CreateFileW\s*\(\s*g_themeSettingsPath\s*,[^;]*CREATE_ALWAYS",
    save_body,
    flags=re.DOTALL,
)
check("final settings file is never truncated before the temporary write succeeds", direct_final_overwrite is None)

passed = 0
for name, ok in checks:
    print(f"{name}: {'PASS' if ok else 'FAIL'}")
    passed += int(ok)
print(f"SUMMARY {passed}/{len(checks)}")
raise SystemExit(0 if passed == len(checks) else 1)
