# minimum cmake version
cmake_minimum_required(VERSION 3.17)

add_library(task2 STATIC task2.h task2.cpp)

# include directory
target_include_directories(task2 PRIVATE intersection utility input)

# link libraries
target_link_libraries(task2 PRIVATE OpenCV intersection utility input)