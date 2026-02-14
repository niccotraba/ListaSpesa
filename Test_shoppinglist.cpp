//Test per la classe ShoppingList

#include "gtest/gtest.h"
#include "ShoppingList.h"
#include <cstdio> //per std::remove

//test per la gestione della lista
TEST(ShoppingListTest, AggiuntaRimozione) {
    ShoppingList lista;
    ShoppingItem item("Pasta", 1, false, "Alimenti", 1.20);
    
    lista.addItem(item);
    ASSERT_EQ(lista.getItems().size(), 1);
    
    lista.removeItem(0);
    EXPECT_TRUE(lista.getItems().empty());
}

//test calcoli
TEST(ShoppingListTest, CalcoloTotale) {
    ShoppingList lista;
    lista.addItem(ShoppingItem("A", 1, false, "", 10.0));
    lista.addItem(ShoppingItem("B", 2, false, "", 5.0)); // 2*5 = 10
    
    EXPECT_DOUBLE_EQ(lista.getTotalCost(), 20.0);
}

//test persistenza
TEST(ShoppingListTest, PersistenzaFile) {
    std::string filename = "test_list.csv";
    ShoppingList listaOrig;
    listaOrig.addItem(ShoppingItem("TestItem", 99));
    
    //salva su file
    EXPECT_TRUE(listaOrig.saveToFile(filename));
    
    //carica da file
    ShoppingList listaNuova;
    EXPECT_TRUE(listaNuova.loadFromFile(filename));
    
    //verifica
    ASSERT_EQ(listaNuova.getItems().size(), 1);
    EXPECT_EQ(listaNuova.getItems()[0].getName(), "TestItem");
    EXPECT_EQ(listaNuova.getItems()[0].getQuantity(), 99);
    
    //pulizia file di test
    std::remove(filename.c_str());
}

//test per la modifica di un elemento
TEST(ShoppingListTest, ModificaElemento) {
    ShoppingList lista;
    ShoppingItem originale("Latte", 1, false, "Alim", 1.0);
    lista.addItem(originale);

    //creazione di un nuovo elemento con le modifiche desiderate
    ShoppingItem modificato("Latte Scremato", 2, true, "Alim", 2.50);

    //modifica dell'elemento nella lista (elemento 0)
    lista.modifyItem(0, modificato);

    //verifica
    const auto& items = lista.getItems();
    ASSERT_EQ(items.size(), 1); // La dimensione non deve cambiare
    EXPECT_EQ(items[0].getName(), "Latte Scremato");
    EXPECT_DOUBLE_EQ(items[0].getPrice(), 2.50);
    EXPECT_EQ(items[0].getQuantity(), 2);
    EXPECT_TRUE(items[0].isPurchased());
}

//test calcolo totale parziale (solo elementi acquistati)
TEST(ShoppingListTest, CalcoloTotaleParziale) {
    ShoppingList lista;
    //aggiungo 3 prodotti
    lista.addItem(ShoppingItem("Pasta", 1, true, "", 2.0));  // PRESO (2.0)
    lista.addItem(ShoppingItem("Sugo", 1, false, "", 3.0));  // NON PRESO
    lista.addItem(ShoppingItem("Vino", 1, true, "", 10.0));  // PRESO (10.0)

    //il costo totale della lista è 2.0 + 3.0 + 10.0 = 15.0
    EXPECT_DOUBLE_EQ(lista.getTotalCost(), 15.0);
    //il costo totale degli elementi non acquistati è 3.0
    EXPECT_DOUBLE_EQ(lista.getPurchasedCost(), 12.0);
}