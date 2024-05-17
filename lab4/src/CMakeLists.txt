FILE(GLOB_RECURSE SRC "*.h" "*.cpp")
add_library(shape ${SRC})
target_link_libraries(shape PRIVATE sfml-graphics sfml-window sfml-system)
target_include_directories(shape PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})