# minimum cmake version
cmake_minimum_required(VERSION 3.17)

add_library(global INTERFACE)

target_include_directories(global INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_sources(global INTERFACE enum.h)