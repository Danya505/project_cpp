cmake_minimum_required(VERSION 3.10)
project(RallyBuilder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    check_point.cpp
    text_report_builder.cpp
    penalty_sum_builder.cpp
    rally_director.cpp
    main.cpp
)

set(HEADERS
    check_point.h
    text_report_builder.h
    penalty_sum_builder.h
    rally_director.h
    report_builder.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})