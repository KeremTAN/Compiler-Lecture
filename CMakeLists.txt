cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 17)
project(Section1-BasicsOfCompiler)

set (PROJECT_DIR ${CMAKE_SOURCE_DIR})

set (PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)

set (PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)

file(GLOB PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/*.cpp)

file(GLOB PROJECT_HEADERS
    ${PROJECT_INCLUDE_DIR}/*.hpp)

find_package(LLVM REQUIRED CONFIG)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
llvm_map_components_to_libnames(llvm_libs support core irreader)
include_directories(${PROJECT_INCLUDE_DIR})


add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} ${llvm_libs})

