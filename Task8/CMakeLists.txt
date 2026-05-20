cmake_minimum_required(VERSION 3.10)
project(Task8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(task8
    main.cpp
    ExpressionFactory.cpp
)

target_include_directories(task8 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
