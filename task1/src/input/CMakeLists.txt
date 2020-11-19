# minimum cmake version
cmake_minimum_required(VERSION 3.17)

add_library(input STATIC readInput.cpp readInput.h)

# include directory
target_include_directories(input PRIVATE global)

# link libraries
target_link_libraries(input PRIVATE global OpenCV)