cmake_minimum_required(VERSION 3.10)

project(TinyImageLib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Lista de arquivos fonte (se você adicionar .cpp futuramente, coloque aqui)
set(SOURCES 
    src/main.cpp
)

# Cria o executável
add_executable(app ${SOURCES})

# Indica ao compilador para buscar os #include na pasta 'include'
# O uso de PUBLIC ou INTERFACE é útil se você transformar isso em biblioteca depois
target_include_directories(app PRIVATE ${INCLUDE_DIR})

# Comando para rodar o projeto de forma mais simples (cmake --build build --target run)
add_custom_target(run
    COMMAND ./app
    DEPENDS app
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Executando o projeto TinyImageLib..."
)