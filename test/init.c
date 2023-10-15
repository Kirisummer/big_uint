#include "init.h"
#include "big_uint.h"

#include <string.h>

int test_copy(const char *name) {
    const char *orig_hex = "51bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4";
    bui_hex_res orig_res = bui_from_hex(orig_hex);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, orig_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, orig_res.hex_st.conv_st);

    bui_alloc_res copy_res = bui_copy(orig_res.bui);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, copy_res.alloc_st);

    const char *copy_hex = bui_hex(copy_res.bui);
    TINYTEST_ASSERT(copy_hex);
    TINYTEST_STR_EQUAL(orig_hex, copy_hex);

    bui_free(&orig_res.bui);
    bui_free(&copy_res.bui);

    return 1;
}

int test_from_uint(const char *name) {
    bui_alloc_res res = bui_from_uint(0xFFFF);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, res.alloc_st);

    const char *hex = bui_hex(res.bui);
    TINYTEST_ASSERT(hex);
    TINYTEST_STR_EQUAL("ffff", hex);

    bui_free(&res.bui);

    return 1;
}

int test_set_uint(const char *name) {
    bui_alloc_res res = bui_from_uint(0xFFFF);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, res.alloc_st);

    bui_alloc_st ow_st = bui_set_uint(&res.bui, 0x1234);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, ow_st);

    const char *hex = bui_hex(res.bui);
    TINYTEST_ASSERT(hex);
    TINYTEST_STR_EQUAL("1234", hex);

    bui_free(&res.bui);

    return 1;
}

// TODO: allocation fail tests

TINYTEST_START_SUITE(BuiInit);
    TINYTEST_ADD_TEST(test_copy, NULL, NULL);
    TINYTEST_ADD_TEST(test_from_uint, NULL, NULL);
    TINYTEST_ADD_TEST(test_set_uint, NULL, NULL);
TINYTEST_END_SUITE();
