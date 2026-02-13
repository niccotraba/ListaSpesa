/*
 * Implementazione della classe ShoppingItem
 */

#include "ShoppingItem.h"
#include <sstream> //serve per formattare bene il testo
#include <iomanip> //serve per i decimali del prezzo
#include <stdexcept> //per std::invalid_argument

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
    std::stringstream ss; //stream per costruire la stringa di descrizione

    //costruzione stringa
    ss << name << " (" << quantity << ") - " << category << " - ";

    //formattazione del prezzo con 2 decimali e simbolo dell'euro
    ss << std::fixed << std::setprecision(2) << price << "€ - ";

    //stato di acquisto
    ss << (purchased ? "Acquistato" : "Da comprare");

    return ss.str();
}

//implementazioni dei metodi per la persistenza
//metodo che converte l'elemento in una stringa CSV per il salvataggio su file. Formato atteso: "nome,quantità,purchased,categoria,prezzo"
std::string ShoppingItem::toString() const {
    std::stringstream ss;
    ss << name << "," << quantity << "," << purchased << "," << category << "," << std::fixed << std::setprecision(2) << price;
    return ss.str();
}

//metodo per creare uno ShoppingItem da una stringa di testo CSV. std::invalid_argument se il formato è errato. Formato atteso: "nome,quantità,purchased,categoria,prezzo"
ShoppingItem ShoppingItem::fromString(const std::string &str) {
    //creo uno stream di input dalla stringa per poterla leggere
    std::istringstream iss(str);

    //variabili temporanee
    std::string name, category, purchasedStr, quantityStr, priceStr;

    //estrazione dei campi dalla stringa, separati da virgole
    //lettura nome
    if (!std::getline(iss, name, ',')) {
        // Se fallisce, la stringa è vuota o malformata
        throw std::invalid_argument("Formato invalido: manca il nome");
    }

    //lettura quantità
    if (!std::getline(iss, quantityStr, ',')) {
        throw std::invalid_argument("Formato invalido: manca la quantità");
    }

    //lettura stato di acquisto
    if (!std::getline(iss, purchasedStr, ',')) {
        throw std::invalid_argument("Formato invalido: manca lo stato");
    }

    //lettura categoria
    if (!std::getline(iss, category, ',')) {
        throw std::invalid_argument("Formato invalido: manca la categoria");
    }

    //lettura prezzo
    if (!std::getline(iss, priceStr, ',')) {
        throw std::invalid_argument("Formato invalido: manca il prezzo");
    }


    //conversione dei campi da stringa a tipi appropriati
    int quantity;      //quantità convertita
    double price;      //prezzo convertito
    bool purchased;    //stato convertito

    try {
        //conversione da stringa a numero intero
        quantity = std::stoi(quantityStr);

        //conversione 1/0 a true/false
        purchased = (purchasedStr == "1");

        //conversione da stringa a numero decimale (double)
        price = std::stod(priceStr);

    } catch (const std::exception&) {
        //se una conversione fallisce viene lanciata un'eccezione
        throw std::invalid_argument("Errore conversione dati numerici");
    }

    //costruzione ritorno
    return ShoppingItem(name, quantity, purchased, category, price);
}

