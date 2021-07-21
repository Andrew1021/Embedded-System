# Embedded System - Puls-Oximeter
## Abstrakt
Kommunikationssysteme wie Smartphones und Smartwatches sind in den letzten
Jahren sehr beliebt geworden. Viele von ihnen verfügen auch über
Gesundheitsüberwachungsfunktionen wie die optische Puls- und Sauerstoffmessung.
In diesem Projekt werden der menschliche Puls sowie die Sauerstoffsättigung des
Blutes mit einem optischen Sensor gemessen und anschließend auf einem LCD
visualisiert.
In der Dokumentation dieses Projektes wird zunächst auf den medizinischen Hintergrund und das
optische Messsystem eingegangen. Danach wird der Entwicklungsprozess der Hard-und Software genauer erläutert.
Am Ende werden die gewonnenen Ergebnisse gezeigt und ein Fazit gezogen.

## Anforderungen
Für die Ausführung werden ein TM4C129E LaunchPad mit TM4C129ENCPDT Microcontroller sowie das Educational BoosterPack MK 2 benötigt.
Für dieses wurde eine Erweiterungsplatine für ein einfaches Pulsoxymeter zusammen mit dem Nellcor-DS100A Fingerclipsensor entwickelt.

![image](https://user-images.githubusercontent.com/50369798/126452260-15f0b47d-9ee1-491c-91f1-e4f12463da49.png)

## Softwareinbetriebnahme
1. Projektordner „V2.0ES_WS20_TM4C129EXL_Puls_Oximeter“ auf PC entpacken
2. Code Composer Studio mit gewünschtem Workspace öffnen
3. Entpackte Projekt in Code Composer Studio importieren
a. Reiter „Project“ => „Import CCS Projects…“ auswählen
b. Im Fenster Punkt „Select Archive File“ auswählen und mit
Schaltfläche „Browse“ nach Projekt suchen
c. Wichtig ist es einen Haken bei „copy projects into workspace“ zu
setzen!
4. Baue Projekt über den Reiter „Project“ => „Build Projekt“
a. Bei Fehlern nachsehen, ob „SW_ROOT“ als Systemvariable
b. und alle nötigen „Include Options“ und „Predefined Symbols“ gesetzt
sind.
5. TM4C129E LaunchPad anstecken und nachsehen, ob es vom PC erkannt
wird
6. Bei Erfolg das Projekt „V2.0ES_WS20_TM4C129EXL_Puls_Oximeter“ über den Reiter „Run“
=> „Debug“ auf das TM4C129E LaunchPad überspielen
7. Abwarten bis das Projekt übertragen wurde und dann über den Reiter
„Run“ => „Resume“ das Programm auf dem TM4C129E LaunchPad
ausführen

## Hardwareinbetriebnahme
1. Die einzelnen Hardwarekomponenten aus der Verpackung entnehmen
und auf eine ESD-geschützte Fläche platzieren
2. Auf Steckplatz 2 (mittlere Steckerleisten) des TM4C129E LaunchPad das
Educational BoosterPack MK 2 (Displaykante zu Ethernetbuchse hin
befestigen)
3. Auf Steckplatz 1 (rechte Steckerleisten) des TM4C129E LaunchPad die
Erweiterungsplatine des Pulsoxymeter befestigen (SUB-D9 Buchse nach
rechts)
4. Mit der SUB-D9 Buchse den SUB-D9 Stecker des Nellcor-DS100A
Fingerclip-Sensores verbinden und kräftig andrücken, dabei die Platine
festhalten
5. USB-Kabel mit Micro-USB-Stecker an die Micro-USB-Buchse (Beschriftung
„DEBUG“) des TM4C129E LaunchPad anschließen und mit dem PC
verbinden
6. Einen Finger (bevorzugt kleiner Finger) in dem Nellcor-DS100A Fingerclip
befestigen und dabei auf möglichst orthogonalen Sitz der LEDs und
Photodiode zueinander achten
7. Die Messergebnisse für den Puls (BPM) und die Sauerstoffsättigung
(SpO2 %) sowie weitere Betriebsmeldungen (INACTIVE, ECO, ERROR)
werden auf dem Display des Educational BoosterPack MK 2 ausgegeben
8. Zudem ertönt bei jedem Herzschlag ein akustisches Signal durch einen
Beeper

## Pin-Out
![image](https://user-images.githubusercontent.com/50369798/126452124-1c1da652-1f20-4b8b-8179-7de6f9dfb62b.png)

