# minimum cmake version
cmake_minimum_required(VERSION 3.17)
project(input VERSION 0.1.0)

# subdirectories
add_subdirectory(src)
add_subdirectory(include)

target_include_directories(input PUBLIC include)
                                    
add_library(input::input ALIAS input)