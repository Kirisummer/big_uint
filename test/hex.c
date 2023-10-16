#include "hex.h"
#include "big_uint.h"

#include <string.h>

int test_hex_overwrite(const char* name) {
    bui_alloc_res res = bui_from_uint(0xFF);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, res.alloc_st);

    const char *ow_hex = "1234567812345678af";
    bui_hex_st hex_st = bui_set_hex(&res.bui, ow_hex);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, hex_st.conv_st);

    const char *out_hex = bui_hex(res.bui);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL(ow_hex, out_hex);

    bui_free(&res.bui);

    return 1;
}

int test_hex_one_block(const char* name) {
    big_uint u = {0};

    const char *in_hex = "1234567812345678";
    bui_hex_st hex_st = bui_set_hex(&u, in_hex);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, hex_st.conv_st);

    char *out_hex = bui_hex(u);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL(in_hex, out_hex);

    bui_free(&u);

    return 1;
}

int test_hex_msb_not_full(const char *name) {
    big_uint u = {0};

    const char *in_hex = "1231234567812345678";
    bui_hex_st hex_st = bui_set_hex(&u, in_hex);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, hex_st.conv_st);

    char *out_hex = bui_hex(u);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL(in_hex, out_hex);

    bui_free(&u);

    return 1;
}

int test_hex_invalid(const char *name) {
    big_uint u = {0};

    const char *in_hex = "1234invalid5678";
    bui_hex_st hex_st = bui_set_hex(&u, in_hex);
    TINYTEST_EQUAL(BUI_HEX_INVFORMAT, hex_st.conv_st);

    TINYTEST_EQUAL(NULL, u.blocks);
    TINYTEST_EQUAL(0, u.alloc);
    TINYTEST_EQUAL(0, u.len);

    bui_free(&u);

    return 1;
}

// TODO: allocation fail tests

TINYTEST_START_SUITE(BuiHex);
    TINYTEST_ADD_TEST(test_hex_overwrite, NULL, NULL);
    TINYTEST_ADD_TEST(test_hex_one_block, NULL, NULL);
    TINYTEST_ADD_TEST(test_hex_msb_not_full, NULL, NULL);
    TINYTEST_ADD_TEST(test_hex_invalid, NULL, NULL);
TINYTEST_END_SUITE();
