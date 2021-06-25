# minimum cmake version
cmake_minimum_required(VERSION 3.17)

add_library(input STATIC readInput.h readInput.cpp)

# include directory
target_include_directories(input PRIVATE utility)

# link libraries
target_link_libraries(input PRIVATE OpenCV utility)