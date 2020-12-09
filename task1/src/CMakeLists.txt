# minimum cmake version
cmake_minimum_required(VERSION 3.17)

find_package(OpenCV REQUIRED)
add_library(OpenCV INTERFACE)
target_include_directories(OpenCV INTERFACE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(OpenCV INTERFACE  ${OpenCV_LIBS})

find_package(Ceres REQUIRED)
add_library(Ceres INTERFACE)
target_include_directories(Ceres INTERFACE ${CERES_INCLUDE_DIRS})
target_link_libraries(Ceres INTERFACE ${CERES_LIBRARIES})

# executable
add_executable(Tasks main.cpp)

# subdirectories
add_subdirectory(utility)
add_subdirectory(input)
add_subdirectory(task1a)
add_subdirectory(task1b)
add_subdirectory(task2)
add_subdirectory(task3)

# link libraries
target_link_libraries(Tasks PRIVATE OpenCV Ceres intersection utility input task1a task1b task2 task3)