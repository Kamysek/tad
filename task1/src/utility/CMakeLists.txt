# minimum cmake version
cmake_minimum_required(VERSION 3.17)

add_library(utility STATIC utility.h utility.cpp)

# include directory
target_include_directories(utility PRIVATE intersection)

# link libraries
target_link_libraries(utility PRIVATE OpenCV intersection)