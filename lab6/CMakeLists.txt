cmake_minimum_required(VERSION 3.26)

project(HTTPUrl)

enable_testing()

#list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)

add_executable(lab_6 main.cpp)
target_link_libraries(lab_6 PRIVATE http)

add_subdirectory(tests)

add_dependencies(lab_6 run_tests)