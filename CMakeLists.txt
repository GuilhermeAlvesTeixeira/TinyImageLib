cmake_minimum_required(VERSION 3.10)
project(TinyImageLib LANGUAGES CXX)

# Padrão C++20 (necessário para std::clamp e melhor suporte a templates)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Variável de entrada configurável (Pode ser mudada com -DINPUT_IMAGE=nome.ppm)
set(INPUT_IMAGE "entrada.ppm" CACHE STRING "Imagem de entrada para o ciclo")

# Coletar arquivos fonte
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Criar o executável
add_executable(app ${SOURCES})

# Incluir diretórios de cabeçalho
target_include_directories(app PUBLIC include)

# Garante que a imagem de entrada esteja na pasta build para o executável achar
if(EXISTS "${CMAKE_SOURCE_DIR}/${INPUT_IMAGE}")
    configure_file("${CMAKE_SOURCE_DIR}/${INPUT_IMAGE}" "${CMAKE_BINARY_DIR}/${INPUT_IMAGE}" COPYONLY)
endif()

# Automação: Compila e executa o ciclo imediatamente
add_custom_command(TARGET app POST_BUILD
    COMMAND ./app ${INPUT_IMAGE}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "------------------------------------------------
Executando ciclo RGB -> YCbCr -> HSV -> RGB...
Imagem: ${INPUT_IMAGE}
------------------------------------------------"
)