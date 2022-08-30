add_library(libarray STATIC
        src/ArrayList.c
        src/LinkedList.c
        src/DoublyLinkedList.c)
# target_link_libraries(libarray PRIVATE libtypes)
target_include_directories(libarray PUBLIC include)


# testing stuff
enable_testing() # Necessary here!

add_executable(
        Array_tests
        tests/ArrayList_tests.cpp
        tests/DoublyLinkedList_tests.cpp)

target_link_libraries(
        Array_tests
        libarray
        libtypes
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Array_tests)

# benchmarking stuff

# benchmarking the get method
add_executable(
        DoublyLinkedList_get_bench
        benchmark/DoublyLinkedList_get_bench.cpp
)

target_link_libraries(
        DoublyLinkedList_get_bench
        libarray
        libtypes
        benchmark::benchmark
        benchmark::benchmark_main
)