from pathlib import Path

root = Path(__file__).resolve().parents[1]
script = (root / 'scripts' / 'Test-GitHubInstaller.ps1').read_text(encoding='utf-8-sig')

checks = []

def check(condition: bool, message: str) -> None:
    checks.append((condition, message))
    print(f"{message}: {'PASS' if condition else 'FAIL'}")

check('AddSeconds(10)' in script and 'Desktopverknüpfung fehlt' in script,
      'desktop shortcut publication has a bounded retry window')
check('function Normalize-WindowsPath' in script,
      'shortcut paths are normalized before comparison')
check('TrimEnd([IO.Path]::DirectorySeparatorChar' in script,
      'directory comparison ignores trailing separators')
check('New-Object -ComObject WScript.Shell' in script,
      'shortcut metadata is read through WScript.Shell first')
check('New-Object -ComObject Shell.Application' in script,
      'shortcut metadata has a Shell.Application fallback')
check('SHORTCUT WScript target' in script and 'SHORTCUT Shell.Application target' in script,
      'resolved shortcut metadata is persisted in diagnostics')
check("if ([string]::IsNullOrWhiteSpace($actualWorkingDirectory))" in script and
      'WARN: Das Arbeitsverzeichnis' in script,
      'empty CI working-directory metadata no longer rejects a valid link')
check('WorkingDirectory="INSTALLFOLDER"' in (root / 'installer' / 'wix' / 'Package.wxs').read_text(encoding='utf-8-sig'),
      'WiX still authors the expected shortcut working directory')
check('[IO.File]::AppendAllText' in script and 'Tee-Object -FilePath $SmokeLog' not in script,
      'installer smoke log uses one consistent UTF-8 writer')
check('Write-SmokeLog "FAIL: $($_.Exception.Message)"' in script,
      'shortcut and installer failures are written to the uploaded smoke log')

failed = [message for ok, message in checks if not ok]
print(f"SUMMARY {len(checks) - len(failed)}/{len(checks)}")
raise SystemExit(1 if failed else 0)
