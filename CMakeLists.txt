cmake_minimum_required(VERSION 3.16)

project("big_uint" LANGUAGES C)
set(C_STANDARD C23)

add_library(big_uint STATIC
    src/bitwise.c
    src/hex.c
    src/init.c
)
target_include_directories(big_uint PUBLIC include)
