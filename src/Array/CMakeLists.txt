add_library(libarray STATIC
        src/ArrayList.c
        src/LinkedList.c)
# target_link_libraries(libarray PRIVATE libtypes)
target_include_directories(libarray PUBLIC include)


# testing stuff
enable_testing() # Necessary here!

add_executable(
        Array_tests
        tests/ArrayList_tests.cpp
)
target_link_libraries(
        Array_tests
        libarray
        libtypes
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Array_tests)