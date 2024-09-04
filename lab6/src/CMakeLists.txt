FILE(GLOB_RECURSE SRC "*.h" "*.cpp")
add_library(http ${SRC})
target_include_directories(http PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})