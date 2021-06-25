# minimum cmake version
cmake_minimum_required(VERSION 3.17.0)
project(Tasks VERSION 0.1.0)

# set cpp version
set(CMAKE_CXX_STANDARD 17)

# subdirectories
add_subdirectory(libs)
add_subdirectory(src)