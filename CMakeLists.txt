cmake_minimum_required(VERSION 3.16)

project("big_uint" LANGUAGES C)
set(C_STANDARD C11)

enable_testing()

add_library(big_uint STATIC
    src/arithmetic.c
    src/bitwise.c
    src/hex.c
    src/init.c
    src/utils.c
)
target_include_directories(big_uint PUBLIC include PRIVATE src)

add_subdirectory(test)
