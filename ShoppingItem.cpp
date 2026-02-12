/*
 * Implementazione della classe ShoppingItem
 */

#include "ShoppingItem.h"
#include <sstream> //serve per formattare bene il testo
#include <iomanip> //serve per i decimali del prezzo

//implementazione del costruttore
ShoppingItem::ShoppingItem(const std::string& name, int quantity, bool purchased,
                           const std::string& category, double price)
    : name(name), quantity(quantity), purchased(purchased), category(category), price(price) {}

//implementazione Setters
void ShoppingItem::setName(const std::string& name_) { name = name_; }
void ShoppingItem::setQuantity(int quantity_) { quantity = quantity_; }
void ShoppingItem::setPurchased(bool purchased_) { purchased = purchased_; }
void ShoppingItem::setCategory(const std::string& category_) { category = category_; }
void ShoppingItem::setPrice(double price_) { price = price_; }

//metodi stato
void ShoppingItem::markAsPurchased() { purchased = true; }
void ShoppingItem::markAsNotPurchased() { purchased = false; }

//implementazione del metodo getDescription
std::string ShoppingItem::getDescription() const {
    std::stringstream ss;

    //costruzione stringa
    ss << name << " (" << quantity << ") - " << category << " - ";

    //formattazione del presso con 2 decimali e simbolo dell'euro
    ss << std::fixed << std::setprecision(2) << price << "€ - ";

    //stato di acquisto
    ss << (purchased ? "Acquistato" : "Da comprare");

    return ss.str();
}