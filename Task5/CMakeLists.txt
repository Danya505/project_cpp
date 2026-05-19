cmake_minimum_required(VERSION 3.10)
project(Logger)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    test.cpp
    log.cpp
    info.cpp
    time.cpp
)

add_executable(logger ${SOURCES})