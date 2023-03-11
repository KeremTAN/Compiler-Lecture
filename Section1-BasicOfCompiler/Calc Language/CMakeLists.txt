cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 17)
project(Section1-BasicsOfCompiler)

set (PROJECT_DIR ${CMAKE_SOURCE_DIR})

set (PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)

set (PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)

set(PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/Front-End/Scanning/Lexer.cpp
    ${PROJECT_SOURCE_DIR}/Front-End/Scanning/Token.cpp
    ${PROJECT_SOURCE_DIR}/Front-End/Parsing/BinaryOp.cpp
    ${PROJECT_SOURCE_DIR}/Front-End/Parsing/Factor.cpp
    ${PROJECT_SOURCE_DIR}/Front-End/Parsing/Parser.cpp
    ${PROJECT_SOURCE_DIR}/Front-End/Parsing/WithDecl.cpp
    ${PROJECT_SOURCE_DIR}/Front-End/Semantic/Sema.cpp
    ${PROJECT_SOURCE_DIR}/Front-End/Semantic/DeclCheck.cpp
    ${PROJECT_SOURCE_DIR}/Back-End/CodeGen.cpp
    ${PROJECT_SOURCE_DIR}/Back-End/ToIRVisitor.cpp
    ${PROJECT_SOURCE_DIR}/Calc.cpp
    ${PROJECT_SOURCE_DIR}/rtcalc.c)

set(PROJECT_HEADERS
    ${PROJECT_INCLUDE_DIR}/Front-End/Scanning/Lexer.hpp
    ${PROJECT_INCLUDE_DIR}/Front-End/Scanning/Token.hpp
    ${PROJECT_INCLUDE_DIR}/Front-End/Parsing/AST.hpp
    ${PROJECT_INCLUDE_DIR}/Front-End/Parsing/BinaryOp.hpp
    ${PROJECT_INCLUDE_DIR}/Front-End/Parsing/Expr.hpp
    ${PROJECT_INCLUDE_DIR}/Front-End/Parsing/Factor.hpp
    ${PROJECT_INCLUDE_DIR}/Front-End/Parsing/Parser.hpp
    ${PROJECT_INCLUDE_DIR}/Front-End/Parsing/WithDecl.hpp
    ${PROJECT_INCLUDE_DIR}/Front-End/Semantic/Sema.hpp
    ${PROJECT_INCLUDE_DIR}/Front-End/Semantic/DeclCheck.hpp
    ${PROJECT_INCLUDE_DIR}/Back-End/CodeGen.hpp
    ${PROJECT_INCLUDE_DIR}/Back-End/ToIRVisitor.hpp)

# -> Path to LLVM 12 installation directory
# set(LLVM_ROOT_DIR "/opt/homebrew/Cellar/llvm@12/12.0.1_1")

# -> Set LLVM_DIR to LLVM 12 installation directory
# set(LLVM_DIR ${LLVM_ROOT_DIR}/lib/cmake/llvm)

find_package(LLVM REQUIRED CONFIG)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
llvm_map_components_to_libnames(llvm_libs support core irreader)
include_directories(${PROJECT_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} ${llvm_libs})