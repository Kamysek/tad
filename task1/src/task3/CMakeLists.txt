# minimum cmake version
cmake_minimum_required(VERSION 3.17)

add_library(task3 STATIC task3.h task3.cpp)

# include directory
target_include_directories(task3 PRIVATE intersection utility input)

# link libraries
target_link_libraries(task3 PRIVATE OpenCV Ceres intersection utility input)