cmake_minimum_required(VERSION 3.8)

project(Volumetric solids)

enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_executable(lab_4 main.cpp)
target_link_libraries(lab_4 PRIVATE solid)

add_subdirectory(test)

add_dependencies(lab_4 run_tests)