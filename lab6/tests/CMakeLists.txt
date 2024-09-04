add_executable(
        unit_tests
        HTTPTests.cpp
)
target_link_libraries(
        unit_tests
        http
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)

add_custom_target(run_tests
        COMMAND unit_tests
        DEPENDS unit_tests
)