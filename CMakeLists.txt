# CMakeLists.txt - LexicAnalyzer Project
# This CMake configuration file sets up the build process for the LexicAnalyzer project,
# which includes creating a static library from source files and an executable for testing.
# - Author: MARDnstuff
# - Date: 2025-11-17

cmake_minimum_required(VERSION 3.16)

# NAME OF THE PROJECT
project(LexicAnalyzer VERSION 1.0 LANGUAGES CXX)

# SETTING THE C++ STANDARD
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CREATE LIBRARY
add_library(lexic STATIC
    src/AnalizadorLL1.cpp
    src/AnalizLexico.cpp
    src/ClaseAFD.cpp
    src/NFA.cpp
    src/ClaseEstado.cpp
    src/ClaseNodo.cpp
    src/ClaseTransicion.cpp
    src/ConIJ.cpp
    src/DescRecGram_Gram.cpp
    src/ElemArreglo.cpp
    src/ER_NFA.cpp
    src/Estado_AnalizLexico.cpp
    src/EvaluadorExp1.cpp
    src/Simb.cpp
    src/SimbTerm.cpp
)

# INCLUDE PUBLIC HEADERS
target_include_directories(lexic PUBLIC include)

# ADD COMPILER WARNINGS
target_compile_options(lexic PRIVATE -Wall -Wextra -Wpedantic)

# CREATE EXECUTABLE FOR TESTING PURPOSES
add_executable(lexic_app
    app/main.cpp
)

# LINK THE LIBRARY TO THE EXECUTABLE
target_link_libraries(lexic_app PRIVATE lexic)