cmake_minimum_required(VERSION 3.16)
project(DreamPOC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Executabilul va fi generat în directorul de build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(DreamPOC
    src/main.cpp
    src/Dream.cpp
)

target_include_directories(DreamPOC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Opțional: warnings utile în Debug
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (MSVC)
        target_compile_options(DreamPOC PRIVATE /W4)
    else()
        target_compile_options(DreamPOC PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()
