# minimum cmake version
cmake_minimum_required(VERSION 3.17)

add_library(task21 STATIC task21.h task21.cpp)

# include directory
target_include_directories(task21 PRIVATE intersection utility input)

# link libraries
target_link_libraries(task21 PRIVATE OpenCV intersection utility input)