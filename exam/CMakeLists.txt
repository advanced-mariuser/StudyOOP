cmake_minimum_required(VERSION 3.26)

project(Exam)

enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)

add_executable(exam main.cpp)