# minimum cmake version
cmake_minimum_required(VERSION 3.17)

add_library(task1a STATIC task1a.h task1a.cpp)

# include directory
target_include_directories(task1a PRIVATE utility input)

# link libraries
target_link_libraries(task1a PRIVATE OpenCV utility input)