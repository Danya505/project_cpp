cmake_minimum_required(VERSION 3.10)

project(TypeList)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/std:c++17)
endif()

add_executable(TypeList tests.cpp)

if(MSVC)
    target_compile_options(TypeList PRIVATE /Zc:preprocessor-)
endif()