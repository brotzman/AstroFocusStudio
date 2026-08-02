# GitHub Actions: Fehler bei optionalen `*_stub.dll`-Dateien

## Symptom

Der Windows-Build brach nach den ersten drei Programmen ab:

```text
Could Not Find ...\device_host\kernel32_stub.dll
```

## Ursache

`lld-link` erzeugt beim Erstellen einer Importbibliothek aus einer `.def`-Datei erfolgreich die angeforderte `.lib`, muss aber keine physische Stub-DLL ausgeben. Die Batchskripte löschten die optionale DLL anschließend bedingungslos. Die dadurch erzeugte Meldung auf dem Fehlerkanal wurde vom strengen PowerShell-CI-Lauf als Abbruch behandelt.

## Korrektur

Die temporären DLLs werden nur noch gelöscht, wenn sie tatsächlich existieren. Die Ausgabe der rein defensiven Bereinigung wird unterdrückt. Betroffen waren:

- `device_host/build-windows-x64.bat`
- `tools/build-windows-x64.bat`

Die Erzeugung und Prüfung der Importbibliotheken bleibt unverändert.
