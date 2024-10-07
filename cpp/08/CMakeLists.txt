cmake_minimum_required(VERSION 3.20)
set(TARGET "vec")


set(SOURCES
    main.cpp
    ../lib/vec/vec2d.cpp
)

project(${TARGET} CXX)

add_executable(${TARGET} ${SOURCES})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../lib/vec")

install(TARGETS ${TARGET})