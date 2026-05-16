cmake_minimum_required(VERSION 3.10)
project(UserGroupManager)

set(CMAKE_CXX_STANDARD 11)

add_executable(usergroup 
    main.cpp
    user.cpp
    group.cpp
    users.cpp
    groups.cpp
)

target_include_directories(usergroup PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})