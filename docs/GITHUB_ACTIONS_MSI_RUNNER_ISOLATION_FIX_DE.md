# GitHub Actions: Burn- und MSI-Tests auf getrennten Windows-Runnern

## Beobachteter Fehler

Der Burn-Bundle-Test war vollständig erfolgreich:

- Installation,
- Payload- und SHA-256-Prüfung,
- drei Health-Checks,
- Reparatur,
- Deinstallation.

Unmittelbar danach blieb eine direkte `msiexec /i`-Installation desselben Produkts auf
demselben GitHub-Runner bis zum Zeitlimit hängen.

## Ursache

Der Fehler lag nicht im kompilierten MSI. Der Test kombinierte zwei unterschiedliche
Windows-Installer-Besitzmodelle in derselben kurzlebigen Windows-Sitzung:

1. Burn installiert, repariert und entfernt das eingebettete MSI.
2. Direkt danach wird dieselbe MSI-Datei erneut über `msiexec` installiert.

Burn kann nach einem erfolgreichen Exit noch Windows-Installer-, Cache- oder
Neustartstatus hinterlassen. Eine unmittelbar folgende rohe MSI-Transaktion kann dann
auf den Installerzustand beziehungsweise die globale Transaktionssperre warten. Ein
längeres Timeout macht diesen Test nicht zuverlässiger.

## Korrektur

Der Workflow baut die Pakete nur einmal und übergibt exakt dieselben Artefakte an zwei
voneinander unabhängige `windows-2022`-Jobs:

- `bundle-test`: Burn-Installation, Health-Checks, Reparatur und Deinstallation,
- `msi-test`: direkte MSI-Installation, Health-Checks, MSI-Reparatur und
  MSI-Deinstallation.

Jeder Job startet auf einer frischen Windows-VM. Burn-Registrierung, MSI-Cache,
Neustartstatus und Installerprozesse können dadurch nicht zwischen beiden Tests
übertragen werden.

Das Skript `scripts/Test-GitHubInstaller.ps1` akzeptiert nur noch die expliziten Modi
`Bundle` und `Msi`. Ein gemischter Lauf ist absichtlich nicht vorgesehen.

## Artefakte und Logs

Die Buildausgaben werden als internes Artefakt
`AstroFocusStudio-3.8.8-Installer-Test-Input` an beide Testjobs übertragen. Die Logs
werden getrennt hochgeladen:

- `AstroFocusStudio-3.8.8-Bundle-Test-Logs`,
- `AstroFocusStudio-3.8.8-MSI-Test-Logs`.

Ein GitHub Release wird erst erstellt, wenn Build, Bundle-Test und MSI-Test bestanden
sind.
