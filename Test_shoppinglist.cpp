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