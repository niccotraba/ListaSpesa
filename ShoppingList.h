/*
 * Lista della spesa principale. Contiene una collezione di ShoppingItem e fornisce metodi per gestire la lista.
 * La classe funge da Subject nel patter Observer.
 */

#ifndef LISTASPESA_SHOPPINGLIST_H
#define LISTASPESA_SHOPPINGLIST_H

#include "Subject.h"
#include "ShoppingItem.h"
#include <vector>
#include <string>

class ShoppingList : public Subject {
private:
    std::vector<ShoppingItem> items; //collezione di elementi della lista della spesa
    std::string listName; //nome della lista della spesa

public:
    //costruttore
    explicit ShoppingList(const std::string& listName = "Lista Spesa");

    //METODI GESTIONE LISTA
    //metodo per aggiungere un prodotto
    void addItem(const ShoppingItem& item);

    //metodo per rimuovere prodotto (tramite indice)
    void removeItem(int index);

    //metodo per modificare un prodotto della lista
    void modifyItem(int index, const ShoppingItem& newItem);

    //metodo per modificare lo stato acquisto
    void togglePurchased(int index);

    //metodo per calcolare il costo totale della lista. Se onlyUnpurchased è true, calcola solo il costo degli elementi non acquistati
    double getTotalCost(bool onlyUnpurchased = false) const;

    //metodo per calcolare il costo totale degli elementi acquistati
    double getPurchasedCost() const;

    //metodo per svuotare la lista
    void clearAll();

    //GETTERS
    //restituisce la lista degli elementi
    const std::vector<ShoppingItem>& getItems() const { return items; }

    //restituisce il nome della lista
    std::string getName() const { return listName; }

    //restituisce il numero di elementi non acquistati
    size_t getUnpurchasedItemCount() const;

    //metodi per la persistenza
    //metodo per salvare la lista su file. Il formato del file è CSV. Restituisce true se il salvataggio è avvenuto con successo, false altrimenti
    bool saveToFile(const std::string& filename) const;

    //metodo per caricare la lista da un file. Il formato del file è CSV. Restituisce true se il caricamento è avvenuto con successo, false altrimenti. Il metodo svuota la lista corrente prima di creare la nuova lista.
    bool loadFromFile(const std::string& filename);

};
#endif //LISTASPESA_SHOPPINGLIST_H