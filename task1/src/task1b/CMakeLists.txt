# minimum cmake version
cmake_minimum_required(VERSION 3.17)

add_library(task1b STATIC task1b.cpp task1b.h)

# include directory
target_include_directories(task1b PRIVATE utility input intersection)

# link libraries
target_link_libraries(task1b PRIVATE OpenCV utility input intersection)