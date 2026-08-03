from pathlib import Path

root = Path(__file__).resolve().parents[1]
installer = (root / 'installer' / 'AstroFocusSetup.ps1').read_text(encoding='utf-8')
updater = (root / 'updater' / 'AstroFocusUpdater.ps1').read_text(encoding='utf-8')
shared = r'Global\AstroFocusStudio.Maintenance'
checks = {
    'installer has named single-instance lock': r'Global\AstroFocusStudio.Installer' in installer and 'Enter-InstallerMutex' in installer,
    'updater has named single-instance lock': r'Local\AstroFocusStudio.Updater' in updater and 'Enter-UpdaterMutex' in updater,
    'installer and updater share one maintenance lock': shared in installer and shared in updater and installer.count(shared) == 1 and updater.count(shared) == 1,
    'shared lock is acquired before installer-specific lock': installer.rfind('Enter-MaintenanceMutex') < installer.rfind('Enter-InstallerMutex'),
    'shared lock is acquired before updater-specific lock': updater.rfind('Enter-MaintenanceMutex') < updater.rfind('Enter-UpdaterMutex'),
    'locks reject simultaneous instances': 'WaitOne(0)' in installer and 'WaitOne(0)' in updater,
    'abandoned shared lock is recovered safely': 'AbandonedMutexException' in installer and 'AbandonedMutexException' in updater,
    'inaccessible shared lock fails closed': 'UnauthorizedAccessException' in installer and 'UnauthorizedAccessException' in updater,
    'damaged installed manifest requires repair': 'Führe zuerst Reparatur oder Rollback aus' in updater,
}
for name, ok in checks.items():
    print(f'{name}: {"PASS" if ok else "FAIL"}')
print(f'SUMMARY {sum(checks.values())}/{len(checks)}')
raise SystemExit(0 if all(checks.values()) else 1)
