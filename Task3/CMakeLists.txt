cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 17)

project(PC)

set (SOURCES
  ${CMAKE_SOURCE_DIR}/main.cpp
  ${CMAKE_SOURCE_DIR}/blockage_diag/blockage_diag.cpp
  ${CMAKE_SOURCE_DIR}/crop_box_filter/crop_box_filter.cpp
)

set (HEADERS
  ${CMAKE_SOURCE_DIR}/filter.hpp
  ${CMAKE_SOURCE_DIR}/Logger.h
  ${CMAKE_SOURCE_DIR}/PointCloud.h
  ${CMAKE_SOURCE_DIR}/blockage_diag/blockage_diag.hpp
  ${CMAKE_SOURCE_DIR}/crop_box_filter/crop_box_filter.hpp
)

add_executable(PC
 ${SOURCES}
 ${HEADERS}
)
