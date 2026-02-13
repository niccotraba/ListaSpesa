cmake_minimum_required(VERSION 3.20)
project(ListaSpesa)

set(CMAKE_CXX_STANDARD 17)

# --- 1. Configurazione Google Test (Scarica in automatico) ---
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# Per Windows/Mac a volte serve forzare il linking statico
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- 2. Configurazione wxWidgets (Grafica) ---
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# --- 3. I tuoi file sorgente (La logica) ---
set(SOURCE_FILES
        Observer.h
        Subject.h
        ShoppingItem.h
        ShoppingItem.cpp
        ShoppingList.h
        ShoppingList.cpp
)

# --- 4. ESEGUIBILE DELL'APP (Main Grafico) ---
add_executable(ListaSpesa main.cpp ${SOURCE_FILES})
target_link_libraries(ListaSpesa ${wxWidgets_LIBRARIES})

# --- 5. ESEGUIBILE DEI TEST (Google Test) ---
add_executable(runTests Test.cpp ${SOURCE_FILES})
target_link_libraries(runTests GTest::gtest_main)