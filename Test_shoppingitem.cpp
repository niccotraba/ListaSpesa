//Test per la classe ShoppingItem

#include "gtest/gtest.h"
#include "ShoppingItem.h"

//test costruttore e getters della classe ShoppingItem
TEST(ShoppingItemTest, CostruttoreEGetters) {
    ShoppingItem item("Latte", 2, false, "Latticini", 1.50);

    EXPECT_EQ(item.getName(), "Latte");
    EXPECT_EQ(item.getQuantity(), 2);
    EXPECT_EQ(item.getCategory(), "Latticini");
    EXPECT_DOUBLE_EQ(item.getPrice(), 1.50);
    EXPECT_FALSE(item.isPurchased());
}

//test setters e metodi di stato della classe ShoppingItem
TEST(ShoppingItemTest, ModificaValori) {
    ShoppingItem item("Pane");
    item.setQuantity(5);
    item.markAsPurchased();

    EXPECT_EQ(item.getQuantity(), 5);
    EXPECT_TRUE(item.isPurchased());
}