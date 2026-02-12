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
#include <optional>

class ShoppingList : public Subject {
private:
    std::vector<ShoppingItem> items; //collezione di elementi della lista della spesa
    std::string listName; //nome della lista della spesa

public:
    //costruttore
    explicit ShoppingList(const std::string& listName = "Lista Spesa");

    //getters
    size_t getUnpurchasedItemCount() const; //restituisce il numero di elementi non acquistati

    //metodi per gestire la lista
    //metodo per aggiungere un prodotto
    void addItem(const ShoppingItem& item);

    //metodo per rimuovere prodotto (tramite indice)
    void removeItem(int index);

    //metodo per modificare lo stato acquisto
    void togglePurchased(int index);

    //metodo per svuotare la lista
    void clearAll();

    //getters
    //restituisce la lista degli elementi
    const std::vector<ShoppingItem>& getItems() const { return items; }

    //restituisce il nome della lista
    std::string getName() const { return listName; }


};
#endif //LISTASPESA_SHOPPINGLIST_H