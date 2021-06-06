find_package(Catch2 REQUIRED)

add_executable(tests test.cpp)
target_link_libraries(tests PRIVATE klib)
target_link_libraries(tests PRIVATE Catch2::Catch2)

add_test(NAME unit_tests COMMAND ./tests)
