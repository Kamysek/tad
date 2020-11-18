cmake_minimum_required(VERSION 3.17)

add_library(happly INTERFACE)

target_include_directories(happly INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_sources(happly INTERFACE happly.h)
