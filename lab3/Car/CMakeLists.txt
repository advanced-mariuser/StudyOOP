cmake_minimum_required(VERSION 3.20)

project(Car)

enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

add_executable(lab_3 main.cpp)
target_link_libraries(lab_3 PRIVATE car)

add_subdirectory(test)