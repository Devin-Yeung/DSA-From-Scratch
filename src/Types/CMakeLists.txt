add_library(libtypes STATIC
        src/Integer.c include/Types/Integer.h)

target_include_directories(libtypes PUBLIC include)