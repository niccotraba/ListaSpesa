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


//implementazione metodo per svuotare la lista
void ShoppingList::clearAll() {
    items.clear();
    notify(); //notifico gli osservatori del cambiamento
}

