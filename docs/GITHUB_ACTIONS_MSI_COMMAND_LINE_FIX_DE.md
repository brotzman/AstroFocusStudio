# GitHub Actions: MSI-Aufruf ohne verdeckten Hilfedialog

## Fehlerbild

Der isolierte MSI-Test startete `msiexec.exe`, erzeugte aber keine `msi-install.log` und lief bis zum Timeout. Das Paket selbst war zuvor bereits erfolgreich über das Burn-Bundle installiert, repariert und entfernt worden.

## Ursache

Die gemeinsame Prozessfunktion setzte bisher **jedes** native Argument in Anführungszeichen. Dadurch wurde aus einer gültigen Windows-Installer-Befehlszeile sinngemäß:

```text
msiexec.exe "/i" "Paket.msi" "/qn" "/l*v" "msi-install.log"
```

`msiexec.exe` kann die in Anführungszeichen gesetzten Optionsschalter als ungültige Befehlszeile behandeln und einen Hilfedialog öffnen. Da der CI-Prozess ohne interaktive Oberfläche läuft, bleibt dieser Dialog unsichtbar. Es wird kein MSI-Protokoll erzeugt und der Prozess endet erst durch das Zeitlimit.

## Korrektur

Die Argumentformatierung setzt nur noch Werte mit Leerzeichen in Anführungszeichen. Optionsschalter bleiben unverändert:

```text
C:\Windows\System32\msiexec.exe /i "Paket.msi" /qn /norestart /L*V! "msi-install.log" REBOOT=ReallySuppress
```

Zusätzlich verwendet der Test den absoluten 64-Bit-Pfad zu Windows Installer. `/L*V!` erzwingt ein ausführliches, unmittelbar geschriebenes Protokoll.

## Erwartetes Ergebnis

Der nächste MSI-Test muss unmittelbar eine `msi-install.log` anlegen. Anschließend werden Installation, drei Health-Checks, Reparatur und Deinstallation auf dem isolierten Windows-Runner geprüft.
