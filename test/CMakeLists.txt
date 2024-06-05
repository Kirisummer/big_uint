cmake_minimum_required(VERSION 3.16)

add_executable(big_uint_test 
    arithmetic.c
    bitwise.c
    hex.c
    init.c
    main.c
)
target_include_directories(big_uint_test PRIVATE ../tinytest ../include)
target_link_libraries(big_uint_test PRIVATE big_uint)
add_test(NAME unit COMMAND big_uint_test)
