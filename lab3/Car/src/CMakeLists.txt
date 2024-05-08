FILE(GLOB_RECURSE SRC "*.h" "*.cpp")
add_library(car ${SRC})
target_include_directories(car PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})