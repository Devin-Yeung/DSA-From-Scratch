add_library(libstack STATIC
        src/LinkedStack.c)

target_link_libraries(libstack PRIVATE libarray)
target_include_directories(libstack PUBLIC include)

# testing stuff
enable_testing() # Necessary here!

add_executable(
        Stack_tests
        tests/LinkedStack_tests.cpp)

target_link_libraries(
        Stack_tests
        libstack
        libarray
        libtypes
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Stack_tests)