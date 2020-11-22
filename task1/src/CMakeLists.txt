# minimum cmake version
cmake_minimum_required(VERSION 3.17)

# find necessary packages
find_package(OpenCV REQUIRED)

add_library(OpenCV INTERFACE)
target_include_directories(OpenCV INTERFACE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(OpenCV INTERFACE  ${OpenCV_LIBS})

add_executable(Task1 main.cpp)

# subdirectories
add_subdirectory(global)
add_subdirectory(input)

# link libraries
target_link_libraries(Task1 PRIVATE OpenCV global input intersection)
