---
layout: schede
title: Progetto 4 - Smart Trash
description: Bidone che ti avvisa tramite una notifica sullo smartphone o su un display LCD
img: /img/trash.jpg
---

<iframe width="560" height="315" src="https://www.youtube.com/embed/Nc9AABQD7J4" frameborder="0" allowfullscreen></iframe>

# Gruppo 4: 
- Federica
- Veronica
- Marco
- Giorgio


Codes and materials for this project can be found [here](https://github.com/OfficineArduinoTorino/ITS-Torino/tree/master/Final%20Projects/gruppo%204%20Smart%20Trash)

# INFORMAZIONI GRUPPO:
Il nostro team è formato da quattro persone: Federica Anzoise, Giorgio Mariotti, Veronica Vacca e Marco Portigliatti. Siamo tutti studenti del ITS-ICT Piemonte, indirizzo Mobile App Design. L’età media si aggira intorno ai 20 anni. Ognuno di noi ha delle capacità tecniche o artistiche differenti tra loro, questo ci aiuta a suddividere il lavoro in base alle competenze per poter sviluppare al meglio il progetto, anche se ognuno di noi partecipa attivamente ad ogni fase di progettazione, per avere una conoscenza a 360 gradi di ogni aspetto strutturale e progettuale del prototipo stesso.

# PROGETTO :
Realizzazione di una spazzatura intelligente.
Pensiamo di creare un bidone che avvisi le strutture di smaltimento rifiuti quando è pieno, tramite una notifica sullo smartphone o tramite altri dispositivi.
E' un progetto pensato per gli enti che si occupano della raccolta rifiuti, in particolare di quei rifiuti meno comuni (tipo pile o materiale elettrico).
Il  progetto che il nostro gruppo intende realizzare è stato ideato dopo aver fatto una attenta analisi riguardante lo smaltimento dei rifiuti elettronici. Per l’appunto il nostro gruppo ha realizzato che al momento non sembrano essere presenti dei veri e propri contenitori per la  raccolta di rifiuti di questo genere. In tal senso il nostro impegno si concentrerà nella realizzazione fisica di questa serie di contenitori.
Il bidone prevede due funzionalità base:  la prima è la capacità nel definire da se quando è completamente pieno e di conseguenza nasce la seconda capacità, ovvero riuscire ad inviare un messaggio ai centri di smaltimento rifiuti perchè vengano a svuotare i bidoni.
Il bidone, che avrà una forma rettangolare, ha le seguenti misure 73x58x106. Mentre il prototipo che sarà in scala 1x3 avrà queste misure, 24x19x35. Il prototipo verrà realizzato con due materiali, legno e plexiglas, tramite la lasercut.
 
# OBIETTIVI:
I nostri obiettivi minimi sono la costruzione del prototipo, funzionante nella sua limitatezza in quanto non connesso realmente al un luogo fisico. Successivamente la possibilità di creare una rete che permetta la comunicazione tra il centro operativo, il camion e il bidone.
Si è pensata alla possibilità di aggiungere all’oggetto un sensore a infrarossi che colleghi bidone e camion, e quindi permetta una comunicazione non verbale tra i due. Comunque l’obiettivo primario è la distribuzione del prodotto in tutta Torino.
Successivamente come obiettivi di vasta grandezza ci siamo prefissati l’idea di realizzare un app che crei il percorso per i camion dipendente da quali bidoni vanno svuotati.

# POSSIBILE MERCATO DI RIFERIMENTO:
Puntiamo agli enti pubblici come l’amiat o direttamente il comune di Torino, per avere la possibilità di distribuire il prodotto su vasta scala e come primo nel suo genere, per poi allargarci in tutta Italia in modo massivo.


# Spazzatura intelligente

Bidone che ti avvisa tramite una notifica sullo smartphone o su un display LCD impiantato sul cassonetto.
E' un progetto pensato per gli enti che si occupano della raccolta rifiuti
In particolare di quei rifiuti meno comuni (tipo pile o materiale elettrico).

**Aggiornamento 16/03/2015**

# Spazzatura intelligente:
Il progetto parte dall’idea di aiutare gli enti pubblici nella raccolta dei rifiuti facendo risparmiare tempo e risorse.
Attraverso un sensore IR di prossimità verrà rilevato il livello di rifiuti presenti nel cassonetto inviando eventualmente un segnale al passaggio della camionetta.
Abbiamo individuato tre tecnologie utilizzabili ( BT 4, GSM e Wi-Fi). Utilizzando il Wi-Fi potremmo optare per la Arduino YUN o un un nuovo tipo di schede di rete a basso costo.


MVP: Come progetto minimo pensiamo di installare il rilevatore a infrarossi e programmare la scheda Arduino in modo che si accenda un led nel caso in cui il cassonetto sia pieno. Tralasciamo momentaneamente la parte relativa alla connessione tra il cassonetto e la camionetta.

TODO:
Realizzazione del progetto funzionante in assenza di cestino e spazzatura (programmazione)
realizzazione case (Arduino + Sensore)
EXTRA: invio mail da YUN via SMTP


Materiali: Per il nostro prototipo saranno necessari i seguenti componenti: 
-Scheda Arduino
-Trasmittente e ricettore IR
- sensore di distanza
-Quantità indefinita di legno/bidone della spazzatura preesistente
-Led 
