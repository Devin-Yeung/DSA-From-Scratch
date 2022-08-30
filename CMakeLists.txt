CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project(DSA-From-Scratch)

set(ASAN_COMPILE_TIME_FLAGS "-fsanitize=address -fsanitize-address-use-after-scope")
set(UBSAN_COMPILE_TIME_FLAGS "-fsanitize=undefined,integer,nullability -fno-sanitize=shift,shift-base,unsigned-shift-base")
set(COVERAGE_FLAGS "-fprofile-instr-generate -fcoverage-mapping")
set(DEBUG_FLAGS "-g -fno-omit-frame-pointer")
set(BENCHMARK_ENABLE_TESTING OFF) # test cases in benchmark lib are not required

set(CMAKE_C_FLAGS "${COVERAGE_FLAGS}")
set(CMAKE_CXX_FLAGS "${COVERAGE_FLAGS}")

option(USE_SAN "use sanitizer check" ON) #ON by default
if (USE_SAN)
    MESSAGE(STATUS "Sanitizer ON")
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} ${DEBUG_FLAGS} ${ASAN_COMPILE_TIME_FLAGS} ${UBSAN_COMPILE_TIME_FLAGS} ${COVERAGE_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEBUG_FLAGS} ${ASAN_COMPILE_TIME_FLAGS} ${UBSAN_COMPILE_TIME_FLAGS} ${COVERAGE_FLAGS}")
else()
    MESSAGE(STATUS "Sanitizer OFF")
endif ()
unset(USE_SAN CACHE) # <---- important! (clearing the option from within CMakeLists.txt after the option was used)


# sub dir
add_subdirectory(src/Array)
add_subdirectory(src/Tree)
add_subdirectory(src/Types)

# gtest
add_subdirectory(lib/googletest)
# benchmark
add_subdirectory(lib/benchmark)


add_executable(playground src/playground.c)
# linking the lib
target_link_libraries(playground libarray)
target_link_libraries(playground libtree)
target_link_libraries(playground libtypes)


# testing stuff
# must enable testing here!
enable_testing()