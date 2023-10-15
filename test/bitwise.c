#include "bitwise.h"
#include "big_uint.h"

#include <string.h>

int test_inv(const char *name) {
    bui_alloc_res res = bui_from_uint(0xFF);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, res.alloc_st);

    bui_inv(&res.bui);

    const char *out_hex = bui_hex(res.bui);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL("ffffffffffffff00", out_hex);

    bui_free(&res.bui);

    return 1;
}

int test_xor(const char *name) {
    bui_hex_res lhs_res = bui_from_hex("a051bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4");
    bui_hex_res rhs_res = bui_from_hex("403db8ad88a3932a0b7e8189aed9eeffb8121dfac05c3512fdb396dd73f6331c");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_alloc_st xor_st = bui_xor(&lhs_res.bui, rhs_res.bui);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, xor_st);

    const char *out_hex = bui_hex(lhs_res.bui);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL("a01182d8299c0ec40ca8bf3f49362e95e4ecedaf82bfd167988972412095b13db8", out_hex);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

int test_or(const char *name) {
    bui_hex_res lhs_res = bui_from_hex("a051bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4");
    bui_hex_res rhs_res = bui_from_hex("403db8ad88a3932a0b7e8189aed9eeffb8121dfac05c3512fdb396dd73f6331c");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_alloc_st xor_st = bui_or(&lhs_res.bui, rhs_res.bui);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, xor_st);

    const char *out_hex = bui_hex(lhs_res.bui);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL("a051bff8ad9cafd72eabffbfc9befffffffcffbffaffdd779afdf3d7fdf7f73fbc", out_hex);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

int test_and(const char *name) {
    bui_hex_res lhs_res = bui_from_hex("a051bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4");
    bui_hex_res rhs_res = bui_from_hex("403db8ad88a3932a0b7e8189aed9eeffb8121dfac05c3512fdb396dd73f6331c");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_and(&lhs_res.bui, rhs_res.bui);

    const char *out_hex = bui_hex(lhs_res.bui);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL("403d208400a113220340808088d16a1b10121078400c1002748196dd62460204", out_hex);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

int test_shift_right(const char *name) {
    bui_hex_res res = bui_from_hex("a051bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, res.hex_st.conv_st);

    bui_shr(&res.bui, 47);

    const char *out_hex = bui_hex(res.bui);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL("140a37ec108295aae4d47837d8131eef636a9ff64f0ff1aa514e983", out_hex);

    bui_free(&res.bui);

    return 1;
}

int test_shift_right_multiblock(const char *name) {
    bui_hex_res res = bui_from_hex("a051bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, res.hex_st.conv_st);

    bui_shr(&res.bui, sizeof(bui_block) * 8 * 2 + 13);

    const char *out_hex = bui_hex(res.bui);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL("5028dfb0420a56ab9351e0df604c7bb", out_hex);

    bui_free(&res.bui);

    return 1;
}

int test_shift_left(const char *name) {
    bui_hex_res res = bui_from_hex("a051bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, res.hex_st.conv_st);

    bui_shl(&res.bui, 47);

    const char *out_hex = bui_hex(res.bui);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL("5028dfb0420a56ab9351e0df604c7bbd8daa7fd93c3fc6a9453a60ebfef3238752000000000000", out_hex);

    bui_free(&res.bui);

    return 1;
}

int test_shift_left_multiblock(const char *name) {
    bui_hex_res res = bui_from_hex("a051bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, res.hex_st.conv_st);

    bui_shl(&res.bui, sizeof(bui_block) * 8 * 2 + 13);

    const char *out_hex = bui_hex(res.bui);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL("140a37ec108295aae4d47837d8131eef636a9ff64f0ff1aa514e983affbcc8e1d4800000000000000000000000000000000000", out_hex);

    bui_free(&res.bui);

    return 1;
}

TINYTEST_START_SUITE(BuiBitwise);
    TINYTEST_ADD_TEST(test_inv, NULL, NULL);
    TINYTEST_ADD_TEST(test_xor, NULL, NULL);
    TINYTEST_ADD_TEST(test_or, NULL, NULL);
    TINYTEST_ADD_TEST(test_and, NULL, NULL);
    TINYTEST_ADD_TEST(test_shift_right, NULL, NULL);
    TINYTEST_ADD_TEST(test_shift_right_multiblock, NULL, NULL);
    TINYTEST_ADD_TEST(test_shift_left, NULL, NULL);
    TINYTEST_ADD_TEST(test_shift_left_multiblock, NULL, NULL);
TINYTEST_END_SUITE();
