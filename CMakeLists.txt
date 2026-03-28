cmake_minimum_required(VERSION 3.10)

project(TinyImageLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app src/main.cpp)

target_include_directories(app PRIVATE include)

add_custom_target(run
    COMMAND app
    DEPENDS app
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)