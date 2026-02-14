/*
* Implementazione della classe ShoppingList.
*/

#include "ShoppingList.h"
#include <fstream>
#include <algorithm>

//implementazione del costruttore
ShoppingList::ShoppingList(const std::string& listName) : listName(listName) {}

//implementazione metodo per contare gli elementi non acquistati (notify non necessario)
size_t ShoppingList::getUnpurchasedItemCount() const {
    size_t count = 0;
    for (const auto& item : items) {
        if (!item.isPurchased()) {
            count++;
        }
    }
    return count;
}

//implementazione metodo per aggiungere un elemento
void ShoppingList::addItem(const ShoppingItem &item) {
    items.push_back(item) ;
    notify(); //notifico gli osservatori del cambiamento
}

//implementazione metodo per rimuovere un elemento (per indice)
void ShoppingList::removeItem(int index) {
    //controllo che l'indice sia valido prima di rimuovere l'elemento
    if (index >= 0 && index < items.size()) {
        items.erase(items.begin() + index);
        notify(); //notifico gli osservatori del cambiamento
    }
}

//implementazione metodo per modificare un elemento della lista (per indice)
void ShoppingList::modifyItem(int index, const ShoppingItem& newItem) {
    if (index >= 0 && index < items.size()) {
        items[index] = newItem; //sovrascrive l'oggetto vecchio
        notify(); //aggiorna la grafica
    }
}

//implementazione metodo per modificare lo statop di acquisto di un elemento (per indice)
void ShoppingList::togglePurchased(int index) {
    if (index >= 0 && index < items.size()) {
        if (items[index].isPurchased()) {
            items[index].markAsNotPurchased();
        } else {
            items[index].markAsPurchased();
        }
        notify(); //notifico gli osservatori del cambiamento
    }
}

//implementazione metodo per calcolare il costo totale della lista
double ShoppingList::getTotalCost(bool onlyUnpurchased) const {
    double totalCost = 0.0;
    for (const auto& item : items) {
        if (!onlyUnpurchased || !item.isPurchased()) {
            totalCost += item.getTotalCost();
        }
    }
    return totalCost;
}


//implementazione metodo per svuotare la lista
void ShoppingList::clearAll() {
    items.clear();
    notify(); //notifico gli osservatori del cambiamento
}

//implementazione metodo per salvare la lista su file
bool ShoppingList::saveToFile(const std::string& filename) const {
    //apertura del file in modalità scrittura. Se il file non esiste, viene creato. Se esiste, viene sovrascritto.
    //creo uno stream di output verso il file.
    std::ofstream file(filename);

    //controllo se il file è stato aperto correttamente
    if (!file.is_open()) {
        return false;
    }

    //scrittura intestazione (opzionale, ma utile per chiarezza del file)
    file << listName << "\n";

    //scrittura degli elementi
    //iteriamo su tutti gli elementi della lista
    for (const auto& item : items) {
        //per ogni elemento: chiamo toString() per generare la stringa CSV, la scrivo nel file ed aggiungo \n per andare a capo
        file << item.toString() << "\n";
    }

    //chiusura file
    file.close();

    //ritorniamo true per indicare successo
    return true;
}


//implementazione metodo per caricare la lista da un file
bool ShoppingList::loadFromFile(const std::string& filename) {
    //apertura file in lettura
    //creo uno stream di input dal file
    std::ifstream file(filename);

    //controllo se il file esiste ed è stato aperto correttamente
    if (!file.is_open()) {
        return false;
    }

    //svuoto la lista corrente per fare spazio ai nuovi dati.
    items.clear();

    //variabile per memorizzare ogni riga letta
    std::string line;

    //scrittura intestazione
    if (std::getline(file, line)) {
        //se la lettura ha successo, assegniamo il nome
        listName = line;
    } else {
        //se la lettura fallisce, significa che il file è vuoto o corrotto, quindi si chiude il file e ritorniamo false
        file.close();
        return false;
    }

    //lettura elementi
    //la lettura continua finché ci sono righe da leggere. Ogni riga dovrebbe rappresentare un elemento della lista
    while (std::getline(file, line)) {
        //controllo sulle righe vuote (potrebbero esserci)
        if (line.empty()) {
            continue;  //ignora le righe vuote
        }

        //analisi della riga
        try {
            //fromString() converte la riga in un oggetto ShoppingItem. Lancia una eccezione se la riga è malformata o corrotta
            ShoppingItem item = ShoppingItem::fromString(line);

            //se la conversione ha successo, aggiungiamo l'elemento alla lista
            items.push_back(item);

        } catch (const std::exception& e) {
         continue; //passa alla prossima riga
        }
    }

    //chiusura del file
    file.close();

    //notifica Observers per aggiornare la visualizzazione con i nuovi dati caricati
    notify();

    //true per indicare successo
    return true;
}