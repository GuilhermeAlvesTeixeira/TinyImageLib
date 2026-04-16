cmake_minimum_required(VERSION 3.10)
project(TinyImageLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INPUT_IMAGE "entrada.ppm" CACHE STRING "Imagem de entrada para o ciclo")

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(app ${SOURCES})

target_include_directories(app PUBLIC include)

if(EXISTS "${CMAKE_SOURCE_DIR}/${INPUT_IMAGE}")
    configure_file("${CMAKE_SOURCE_DIR}/${INPUT_IMAGE}" "${CMAKE_BINARY_DIR}/${INPUT_IMAGE}" COPYONLY)
endif()