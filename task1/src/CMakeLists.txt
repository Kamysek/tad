# minimum cmake version
cmake_minimum_required(VERSION 3.17)

# find necessary packages
find_package( OpenCV REQUIRED )

# include directories
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(Task1 main.cpp)

# subdirectories
add_subdirectory(input)

# link libraries
target_link_libraries(Task1 ${OpenCV_LIBS} input)
