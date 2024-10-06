set(TARGET "name_age")
project(${TARGET} CXX)
set(SOURCES
name_age.cpp
 )
 add_executable(${TARGET} ${SOURCES})

 install(TARGETS ${TARGET})