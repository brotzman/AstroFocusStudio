# GitHub Actions: Exitcode 0xC0000409 beim Gerätehost

## Symptom

Der installierte `AstroFocusCameraHost.exe --health-check` endete auf dem
Windows-Runner mit dem dezimalen Exitcode `-1073740791`. Als vorzeichenloser
Windows-Status entspricht dies `0xC0000409` (`STATUS_STACK_BUFFER_OVERRUN` /
Security-Cookie-Fast-Fail).

## Ursache

Alle Programme verwendeten einen eigenen no-CRT-Einstieg
`WinMainCRTStartup`, der zusammen mit der eigentlichen Anwendung mit `/GS`
kompiliert wurde. Der Compiler legte deshalb beim Eintritt bereits den
aktuellen Security Cookie auf dem Stack ab. Erst danach rief die Funktion
`__security_init_cookie()` auf und änderte den globalen Cookie. Bei einem
frühen Rückweg, etwa beim Health-Check, verglich die `/GS`-Epilogprüfung den
alten Stackwert mit dem neu initialisierten globalen Wert und löste dadurch
einen falschen Stack-Overflow-Fast-Fail aus.

## Korrektur

`common/security_entry.cpp` enthält nun den einzigen Programmeinstieg. Diese
kleine Übersetzungseinheit wird ausdrücklich mit `/GS-` kompiliert und führt
nur drei Schritte aus:

1. Security Cookie initialisieren.
2. Die mit `/GS` kompilierte Funktion `AstroFocusApplicationMain()` aufrufen.
3. Nur als Rückfall den Prozess mit Exitcode 0 beenden.

Die eigentliche Anwendungslogik aller sieben Programme bleibt weiterhin mit
`/GS` geschützt. Die Änderung gilt für Frontend, Engine,
Fokussierer-Setup, beide Gerätehosts sowie Setup- und Updater-Launcher.

## Regression

`tests/security_cookie_startup_validation_390.py` prüft unter anderem:

- genau eine Definition von `WinMainCRTStartup`,
- Initialisierung vor dem Aufruf der geschützten Anwendungslogik,
- `/GS-` nur für Cookie und Einstieg,
- `/GS` für die eigentlichen Programmübersetzungseinheiten,
- Einbindung des gemeinsamen Einstiegs in alle Windows- und Cross-Builds.
