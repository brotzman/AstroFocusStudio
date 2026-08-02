# GitHub Actions: WiX-5-Fehler WIX0021 bei Desktopverknüpfung

## Fehler

WiX 5 akzeptiert `CommonDesktopFolder` nicht als Wert von `StandardDirectory/@Id` und beendet den MSI-Build mit `WIX0021`.

## Korrektur

Die Desktopkomponente verwendet jetzt `DesktopFolder`. Das MSI ist `perMachine`; Windows Installer setzt `DesktopFolder` deshalb im All-Users-Kontext auf den öffentlichen Desktop.

```xml
<StandardDirectory Id="DesktopFolder">
  <Component Id="CmpDesktopShortcut" Guid="*" Bitness="always64">
    ...
  </Component>
</StandardDirectory>
```

Der Vertragstest prüft zusätzlich, dass `CommonDesktopFolder` nicht mehr vorkommt und der Paketkontext weiterhin `perMachine` ist.
