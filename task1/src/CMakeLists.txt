# minimum cmake version
cmake_minimum_required(VERSION 3.17)

# find necessary packages
find_package(OpenCV REQUIRED)

add_library(OpenCV INTERFACE)
target_include_directories(OpenCV INTERFACE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(OpenCV INTERFACE  ${OpenCV_LIBS})

# executable
add_executable(Tasks main.cpp)

# subdirectories
add_subdirectory(utility)
add_subdirectory(input)
add_subdirectory(task1a)
add_subdirectory(task1b)
add_subdirectory(task2)

# link libraries
target_link_libraries(Tasks PRIVATE OpenCV intersection utility input task1a task1b task2)