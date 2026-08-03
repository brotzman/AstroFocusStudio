# Kontinuierliche Fokusnachführung in AstroFocus Studio 3.9.0

## Ziel und Umfang

Die neue Expertenfunktion **Nachführung** hält den Fokus während einer laufenden Serie stabil, ohne regelmäßig eine vollständige Autofokuskurve aufzunehmen. Sie verwendet die normalen Live-Fokusbilder von AstroFocus Studio und bewegt den Fokussierer ausschließlich **zwischen** zwei abgeschlossenen Belichtungen.

Eine laufende Hauptbelichtung wird niemals durch eine Motorfahrt verändert. Die Engine setzt den Belichtungszustand zuerst auf beendet, wertet anschließend das robuste Messfenster aus und startet erst danach gegebenenfalls eine begrenzte Mikrokorrektur. Das nächste normale Bild dient als Kontrollmessung.

## Betriebsarten

### Prädiktiv

Verwendet das aus erfolgreichen Fokusläufen gelernte Temperaturmodell. Liegt das Modellziel außerhalb der konfigurierten Totzone, wird die Abweichung auf die maximale Mikrokorrektur begrenzt und zwischen zwei Bildern angefahren.

Voraussetzungen:

- mindestens drei belastbare Temperatur-/Positionspunkte,
- gültige Fokussierertemperatur,
- verbundener absoluter Fokussierer,
- sichere Fokuszone.

### Bildbasiert

Bildet aus mehreren stabilen Livebildern einen robusten Median aus FWHM und HFR. Erst eine nachhaltige Verschlechterung oberhalb der Auslöseschwelle startet eine kleine Probe in der bevorzugten oder zuletzt erfolgreichen Richtung.

Die nächsten normalen Bilder prüfen, ob sich die Metrik ausreichend verbessert hat. Bei fehlender Bestätigung fährt der Fokussierer zur Ausgangsposition zurück.

### Hybrid

Verwendet das Temperaturmodell zur Richtungs- und Zielinformation, bestätigt die Wirkung aber bildbasiert. Ist noch kein Temperaturmodell vorhanden, arbeitet die Funktion wie die bildbasierte Nachführung.

## Sicherheits- und Qualitätsregeln

Eine Korrektur ist nur zulässig, wenn:

- keine Belichtung aktiv ist,
- Kamera und Fokussierer verbunden sind,
- die aktuelle absolute Position bekannt ist,
- kein Autofokus, Schritt-Assistent oder Backlash-Lauf aktiv ist,
- kein ASCOM-Setupdialog reserviert ist,
- keine Gerätewiederherstellung oder andere Fokusbewegung läuft,
- genügend geeignete Sterne vorhanden sind,
- Stabilität, SNR und daraus berechnete Regelqualität die Mindestwerte erfüllen,
- das Ziel vollständig innerhalb der sicheren Fokuszone liegt.

Jede Probe ist auf die konfigurierte maximale Schrittzahl begrenzt. Nach der Motorfahrt folgt eine Beruhigungszeit. Eine Korrektur gilt erst nach mehreren verbesserten Kontrollbildern als angenommen.

Nicht bestätigte Korrekturen werden zurückgenommen. Nach wiederholter Uneindeutigkeit kann optional ein vollständiger Autofokus als sicherer Fallback starten. Nach drei nicht bestätigten Mikrokorrekturen pausiert die Nachführung und muss ausdrücklich freigegeben werden.

Manuelle Fokusbewegungen, Filteroffset-Bewegungen und ein erfolgreicher vollständiger Autofokus setzen beziehungsweise erneuern die Nachführungsreferenz kontrolliert.

## Bedienoberfläche

Der neue Reiter **Nachführung** enthält:

- Aktivierung,
- Auswahl Prädiktiv/Bildbasiert/Hybrid,
- vollständigen Autofokus als Fallback,
- Messfenster in Bildern,
- Totzone in Schritten,
- maximale Mikrokorrektur,
- Mindest-Regelqualität,
- Mindestverbesserung der Kontrollmessung,
- Beruhigungszeit,
- Referenz-Reset und Wiederfreigabe,
- Status, Begründung, Regelqualität, geschätzte Abweichung und Drift,
- Verlauf von Position, Regelziel und Korrekturmarken.

Das Layout verwendet eine responsive obere Zweispaltenstruktur. Bei schmalerem Platz wird die separate Statusspalte ausgeblendet, statt Bedienelemente über den rechten Rand zu schieben. Lange Statusmeldungen sind scrollbar; die sicherheitsrelevante Erläuterung besitzt einen eigenen, umbrochenen Bereich. Das Diagramm bleibt unterhalb aller Bedienelemente und erhält mindestens 100 Pixel Höhe.

## Bewusste Grenze dieser Version

Version 3.9.0 koppelt noch keine separate Guidekamera, keinen OAG-Leitsternstrom und kein ONAG-System an die Engine. Daher gibt es keine echte Messung und Motorregelung parallel zu einer laufenden Hauptbelichtung. Ebenso besteht noch keine direkte Synchronisation mit einer fremden Aufnahmesoftware.

Die umgesetzte Funktion ist eine unterbrechungsarme **Zwischenbild-Nachführung** innerhalb des AstroFocus-Livestreams. Die normalen Bilder werden als Messquelle weiterverwendet; nur während einer erforderlichen Mikrokorrektur und Beruhigungszeit wird der Start des nächsten AstroFocus-Bildes kurz zurückgehalten.
