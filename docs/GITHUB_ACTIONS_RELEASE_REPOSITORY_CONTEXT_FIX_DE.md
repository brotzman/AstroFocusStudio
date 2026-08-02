# GitHub-Actions-Fix: Release-Job ohne lokales Git-Repository

## Fehlerbild

Der Release-Job brach mit folgender Meldung ab:

```text
failed to run git: fatal: not a git repository (or any of the parent directories): .git
```

## Ursache

Der Release-Job lädt nur die zuvor geprüften Release-Artefakte herunter. Er führt bewusst keinen erneuten Checkout des Quellcodes aus. Die Befehle `gh release view`, `gh release upload` und `gh release create` wurden jedoch ohne explizites Repository ausgeführt. GitHub CLI versuchte deshalb, das Ziel-Repository aus einem lokalen `.git`-Verzeichnis zu bestimmen.

## Korrektur

Der Workflow setzt nun:

```yaml
GH_REPO: ${{ github.repository }}
```

und übergibt bei jedem Release-Befehl ausdrücklich:

```text
--repo "$GH_REPO"
```

Damit ist der Release-Job unabhängig von einem lokalen Git-Checkout. Tag und Release werden weiterhin erst nach bestandenem Windows-Build sowie bestandenen Bundle- und MSI-Tests veröffentlicht.
