include(AddCatch2)

add_executable(
  unit_tests
  CarTest.cpp
)
target_link_libraries(
  unit_tests PRIVATE car Catch2::Catch2WithMain
)

include(Ctest)
include(Catch)
catch_discover_tests(unit_tests)

add_custom_target(run_tests
    COMMAND unit_tests
    DEPENDS unit_tests
)