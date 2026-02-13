#include "gtest/gtest.h"
#include "ShoppingList.h"
#include "ShoppingItem.h"

// Test 1: Verifica che la lista appena creata sia vuota
TEST(ShoppingListTest, CostruttoreListaVuota) {
    ShoppingList lista("Mia Lista");
    EXPECT_EQ(lista.getName(), "Mia Lista");
    EXPECT_TRUE(lista.getItems().empty());
    EXPECT_EQ(lista.getUnpurchasedItemCount(), 0);
}

// Test 2: Aggiunta elementi
TEST(ShoppingListTest, AggiuntaElemento) {
    ShoppingList lista;
    ShoppingItem item("Latte", 2, false, "Latticini", 1.50);

    lista.addItem(item);

    ASSERT_EQ(lista.getItems().size(), 1);
    EXPECT_EQ(lista.getItems()[0].getName(), "Latte");
}

// Test 3: Rimozione elementi
TEST(ShoppingListTest, RimozioneElemento) {
    ShoppingList lista;
    ShoppingItem item("Pane");
    lista.addItem(item);

    lista.removeItem(0);

    EXPECT_TRUE(lista.getItems().empty());
}

// Test 4: Calcolo Totale
TEST(ShoppingListTest, CalcoloTotale) {
    ShoppingList lista;
    lista.addItem(ShoppingItem("Latte", 2, false, "", 1.50)); // 3.00
    lista.addItem(ShoppingItem("Pane", 1, false, "", 1.00));  // 1.00

    EXPECT_DOUBLE_EQ(lista.getTotalCost(), 4.00);
}

// Test 5: Persistenza
TEST(ShoppingListTest, SalvataggioCaricamento) {
    std::string filename = "test_gtest.csv";
    ShoppingList listaOrig;
    listaOrig.addItem(ShoppingItem("Mela", 5, true, "Frutta", 0.50));

    EXPECT_TRUE(listaOrig.saveToFile(filename));

    ShoppingList listaNuova;
    EXPECT_TRUE(listaNuova.loadFromFile(filename));

    ASSERT_EQ(listaNuova.getItems().size(), 1);
    EXPECT_EQ(listaNuova.getItems()[0].getName(), "Mela");

    std::remove(filename.c_str());
}