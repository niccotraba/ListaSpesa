/*
* Interfaccia dell'oggetto che rappresenta un elemento della lista della spesa.
 * Contiene le informazioni relative all'elemento.
 */

#ifndef LISTASPESA_SHOPPINGITEM_H
#define LISTASPESA_SHOPPINGITEM_H

#include <string>

// Classe che rappresenta un elemento della lista della spesa
class ShoppingItem {
private:
    std::string name; //nome dell'elemento
    int quantity; //quantità dell'elemento
    bool purchased; //stato di acquisto dell'elemento: true se acquistato, false altrimenti
    std::string category; //categoria dell'elemento (es. "Frutta", "Verdura", "Latticini", "Generale", ecc.)
    double price; //prezzo dell'elemento (opzionale, default 0.0)

public:
    //costruttore
    ShoppingItem(const std::string& name, int quantity = 1, bool purchased = false, const std::string& category = "Generale", double price = 0.0);

    //getters
    const std::string& getName() const { return name; }
    int getQuantity() const { return quantity; }
    bool isPurchased() const { return purchased; }
    const std::string& getCategory() const { return category; }
    double getPrice() const { return price; }

    //setters
    void setName (const std::string& name_);
    void setQuantity (int quantity_);
    void setPurchased (bool purchased_);
    void setCategory (const std::string& category_);
    void setPrice (double price_);

    //metodo che segna l'elemento come acquistato
    void markAsPurchased();

    //metodo che segna l'elemento come non acquistato
    void markAsNotPurchased();

    //metodo che restituisce una descrizione dell'elemento. Formato atteso: "nome (quantità) - categoria - prezzo - stato di acquisto"
    std::string getDescription() const;

};

#endif //LISTASPESA_SHOPPINGITEM_H