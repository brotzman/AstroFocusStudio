from pathlib import Path
src=Path(__file__).resolve().parents[1]
t=(src/'updater'/'AstroFocusUpdater.ps1').read_text(encoding='utf-8')
checks=[]
def ck(name,ok):
    checks.append((name,ok)); print(f'{name}: {"PASS" if ok else "FAIL"}')
ck('missing install manifest does not impersonate bundled version', "return [version]'0.0.0'" in t and 'return $BundledVersion' not in t.split('function Get-InstalledVersion',1)[1].split('function Test-DevelopmentModeAllowed',1)[0])
ck('invalid manifest is logged', 'Kein gültiges Installationsmanifest vorhanden' in t)
print(f'SUMMARY {sum(v for _,v in checks)}/{len(checks)}')
raise SystemExit(0 if all(v for _,v in checks) else 1)
