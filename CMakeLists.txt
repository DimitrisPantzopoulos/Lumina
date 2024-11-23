# CMake minimum version
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(LuminaV6 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Option for specifying executable name
set(EXE_NAME "LuminaV6" CACHE STRING "Name of the engine executable")

set(CMAKE_CXX_COMPILER "g++" CACHE STRING "C++ compiler")

set(EXE_NAME ${EXE_NAME} CACHE STRING "Output binary name")

# Specify source files
set(SOURCES
    main.cpp
    Lumina.cpp
    Evaluation/Eval.cpp
    Evaluation/EvalHelp.cpp
    MoveOrdering/Orderer.cpp
    PST/PST.cpp
    TT/TT.cpp
    Book/Book.cpp
    Helper/HelperFunctions.cpp
    Helper/SEE.cpp
)

# Define the executable using the EXE_NAME variable
add_executable(${EXE_NAME} ${SOURCES})

target_include_directories(LuminaV6 PRIVATE "ChessLib/include")

# Ensure the executable is named correctly for OpenBench
set_target_properties(${EXE_NAME} PROPERTIES OUTPUT_NAME ${EXE_NAME})