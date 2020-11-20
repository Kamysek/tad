# minimum cmake version
cmake_minimum_required(VERSION 3.17)

add_library(global STATIC enum.h helper.cpp helper.h)

# link libraries
target_link_libraries(global PRIVATE OpenCV)