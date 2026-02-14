# Lista della Spesa C++

Applicazione desktop per la gestione di una lista della spesa, sviluppata in C++ utilizzando il framework grafico **wxWidgets** e l'architettura **Observer Pattern**. Include unit testing con **Google Test**.

## Funzionalità

* **Gestione Prodotti**: Aggiunta, modifica e rimozione di articoli.
* **Stato Acquisto**: Checkbox per spuntare gli articoli presi/da prendere.
* **Calcolo Dinamico**:
    * *Totale Lista*: Costo complessivo teorico.
    * *Totale Carrello*: Costo parziale degli articoli già spuntati.
* **Persistenza**: Salvataggio e caricamento dati su file CSV.
* **GUI Nativa**: Interfaccia grafica che si adatta al sistema operativo (Windows/macOS/Linux).


## Architettura

Il progetto segue il pattern **Observer**:
* **Subject (ShoppingList)**: Gestisce i dati e la logica di business. Notifica gli osservatori quando i dati cambiano.
* **Observer (MainFrame)**: L'interfaccia grafica si iscrive alle notifiche e si ridisegna automaticamente senza accoppiamento stretto.
* **Unit Testing**: La logica è disaccoppiata dalla GUI, permettendo test isolati su `ShoppingList` e `ShoppingItem`.

---
Autore: Niccolò Trabalzini
Esame: Laboratorio di Programmazione
