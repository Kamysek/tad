# minimum cmake version
cmake_minimum_required(VERSION 3.17)

add_library(task1b STATIC task1b.h task1b.cpp)

# include directory
target_include_directories(task1b PRIVATE intersection utility input)

# link libraries
target_link_libraries(task1b PRIVATE OpenCV intersection utility input)