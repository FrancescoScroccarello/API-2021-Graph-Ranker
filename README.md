# Prova finale: algoritmi e strutture dati
Applicazione pratica delle tecniche apprese nel modulo di algoritmi e strutture dati del corso di Algoritmi e Principi dell'Informatica tramite l'implementazione di una soluzione ad un problema prestando attenzione ad aspetti concreti di efficienza del codice.
L'obiettivo del progetto è la gestione di una classifica tra grafi diretti pesati; la classifica tiene traccia dei migliori k grafi, sulla base della somma dei cammini più brevi tra il nodo 0 e tutti gli altri nodi raggiungibili da esso. Il programma da realizzare riceve in ingresso due parametri, d e k, ed una sequenza di comandi tra AggiunguGrafo (passato tramite matrice di adiacenza) e Topk. 
* d: dimensione dei grafi
* k: lunghezza della classifica
* AggiungiGrafo: richiede di aggiungere un grafo pesato a quelli considerati per la classifica, passato per matrice di adiacenza
* TopK: stampa i valori degli indici dei top k grafi migliori

##Tool usati
* Linguaggio: C
* Analisi di tempo e memoria: Valgrind
* Editor: Visual Studio Code

##Additional constraints:
* Nessuna libreria esterna al di là della libreria standard del C
* Dati ricevuti in ingresso tramite stdin, risultati da fornire su stdout
* No multithreading
