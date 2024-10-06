set(TARGET "calculator")
project(${TARGET} CXX)
set(SOURCES
calculator.cpp
variable.cpp
token.cpp
 )
 add_executable(${TARGET} ${SOURCES})

 install(TARGETS ${TARGET})