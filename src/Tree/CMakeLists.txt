add_library(libtree STATIC
        src/BinaryTree.c)

target_link_libraries(libtree PRIVATE libarray)

target_include_directories(libtree PUBLIC include)


# testing stuff
enable_testing() # Necessary here!

add_executable(
        Tree_tests
        tests/BSTree_tests.cpp
)
target_link_libraries(
        Tree_tests
        libtree
        libtypes
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Tree_tests)
