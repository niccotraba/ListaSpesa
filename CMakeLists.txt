cmake_minimum_required(VERSION 3.20)
project(ListaSpesa)

set(CMAKE_CXX_STANDARD 20)

# Cerca wxWidgets installato nel sistema
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# Aggiunge l'eseguibile (se aggiungi file .cpp in futuro, mettili qui dopo main.cpp)
add_executable(ListaSpesa main.cpp)

# Collega la grafica all'eseguibile
target_link_libraries(ListaSpesa ${wxWidgets_LIBRARIES})
