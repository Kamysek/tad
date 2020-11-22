# minimum cmake version
cmake_minimum_required(VERSION 3.17)

add_library(utility STATIC utility.cpp utility.h)

# link libraries
target_link_libraries(utility PRIVATE OpenCV)