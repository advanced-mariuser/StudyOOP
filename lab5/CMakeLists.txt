cmake_minimum_required(VERSION 3.26)

project(Date)

enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_executable(lab_5 main.cpp)
target_link_libraries(lab_5 PRIVATE date)

add_subdirectory(tests)

add_dependencies(lab_5 run_tests)