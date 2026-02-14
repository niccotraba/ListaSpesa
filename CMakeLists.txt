cmake_minimum_required(VERSION 3.20)
project(ListaSpesa)

set(CMAKE_CXX_STANDARD 17)

# Configurazione di Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# Runtime library condivisa per Google Test (necessario su Windows)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Configurazione wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# Files sorgente comuni (GUI + Test)
set(SOURCE_FILES
        Observer.h
        Subject.h
        ShoppingItem.h
        ShoppingItem.cpp
        ShoppingList.h
        ShoppingList.cpp
)

# Eseguibile principale (GUI)
add_executable(ListaSpesa
        main.cpp
        MainFrame.h
        MainFrame.cpp
        ${SOURCE_FILES})
target_link_libraries(ListaSpesa ${wxWidgets_LIBRARIES})

# Eseguibile per i test (Unit Test)
add_executable(runTests
        Test_shoppingitem.cpp
        Test_shoppinglist.cpp
        ${SOURCE_FILES})
target_link_libraries(runTests GTest::gtest_main)