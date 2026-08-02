# Standardverhalten des Hauptfensters unter Windows

Das Hauptfenster von AstroFocus Studio wurde bislang beim Minimieren zusätzlich mit
`ShowWindow(..., SW_HIDE)` verborgen und in den Infobereich verschoben. Wenn das
Tray-Symbol nicht sichtbar oder erreichbar war, blieb nur noch der Prozess im
Task-Manager.

Der Sonderpfad wurde entfernt. Das Hauptfenster verwendet weiterhin die normalen
Windows-Stile für Titelleiste, Systemmenü, Minimieren, Maximieren und Größenänderung.
Beim Minimieren bleibt es nun als normale Schaltfläche in der Windows-Taskleiste
sichtbar und kann von dort wiederhergestellt oder maximiert werden.

Die Engine bleibt davon unberührt. Sie ist ein Hintergrundprozess und besitzt kein
regulär angezeigtes Benutzerfenster.
