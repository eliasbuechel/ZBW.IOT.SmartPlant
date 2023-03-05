###### SmartPlant

Es Wurden die Komponenten Gewächshaus und Wetterdaten entwickelt.

Inbetriebnahme: - MQTT Server auf lokalem Rechner laufen lassen. - Netzwerk
Konfiguration der Komponenten anpassen. - MQTT Konfiguration anpassen. -
Komponenten auf Zielsystem laden (darauf achten, dass die richtige Komponente
aktiviert ist)

INFO:

Gewächshaus: Das Gewächshaus wurde versucht mit Sensor Simulationen zu
simulieren. Ausserdem hört er auf Wetterdaten vom Broker. Auf dem LED streifen
wurde versucht die Signale zu Visualisieren. Der Niederschlag kann mit dem
Button simuliert werden.

Wetterdaten: Das Programm holt Zyklisch Wetterdaten vom Internet, wertet diese
aus. Die werden dann zum Broker geschickt.
