# minimum cmake version
cmake_minimum_required(VERSION 3.17)

add_library(intersection INTERFACE)

target_include_directories(intersection INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_sources(intersection INTERFACE customGeometry.h raybox.h)