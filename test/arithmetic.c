#include "arithmetic.h"
#include "big_uint.h"

#include <string.h>

/* COMP **********************************************************************/
int test_arithmetic_comp_less_val(const char *name) {
    bui_hex_res lhs_res = bui_from_hex("36f028580bb02cc8272a9a020f4200e346e276ae664e45ee80745574e2f5ab80");
    bui_hex_res rhs_res = bui_from_hex("70983d692f648185febe6d6fa607630ae68649f7e6fc45b94680096c06e4fadb");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_comp_res comp_res = bui_comp(lhs_res.bui, rhs_res.bui);
    TINYTEST_EQUAL(BUI_COMP_LS, comp_res);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

int test_arithmetic_comp_less_len(const char *name) {
    bui_hex_res lhs_res = bui_from_hex(  "36f028580bb02cc8272a9a020f4200e346e276ae664e45ee80745574e2f5ab80");
    bui_hex_res rhs_res = bui_from_hex("0136f028580bb02cc8272a9a020f4200e346e276ae664e45ee80745574e2f5ab80");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_comp_res comp_res = bui_comp(lhs_res.bui, rhs_res.bui);
    TINYTEST_EQUAL(BUI_COMP_LS, comp_res);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

int test_arithmetic_comp_eq(const char *name) {
    bui_hex_res lhs_res = bui_from_hex("36f028580bb02cc8272a9a020f4200e346e276ae664e45ee80745574e2f5ab80");
    bui_hex_res rhs_res = bui_from_hex("36f028580bb02cc8272a9a020f4200e346e276ae664e45ee80745574e2f5ab80");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_comp_res comp_res = bui_comp(lhs_res.bui, rhs_res.bui);
    TINYTEST_EQUAL(BUI_COMP_EQ, comp_res);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

int test_arithmetic_comp_greater_val(const char *name) {
    bui_hex_res lhs_res = bui_from_hex("70983d692f648185febe6d6fa607630ae68649f7e6fc45b94680096c06e4fadb");
    bui_hex_res rhs_res = bui_from_hex("36f028580bb02cc8272a9a020f4200e346e276ae664e45ee80745574e2f5ab80");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_comp_res comp_res = bui_comp(lhs_res.bui, rhs_res.bui);
    TINYTEST_EQUAL(BUI_COMP_GT, comp_res);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

int test_arithmetic_comp_greater_len(const char *name) {
    bui_hex_res lhs_res = bui_from_hex("0136f028580bb02cc8272a9a020f4200e346e276ae664e45ee80745574e2f5ab80");
    bui_hex_res rhs_res = bui_from_hex(  "36f028580bb02cc8272a9a020f4200e346e276ae664e45ee80745574e2f5ab80");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_comp_res comp_res = bui_comp(lhs_res.bui, rhs_res.bui);
    TINYTEST_EQUAL(BUI_COMP_GT, comp_res);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

/* ADD ***********************************************************************/

int test_arithmetic_add(const char *name) {
    bui_hex_res lhs_res = bui_from_hex("36f028580bb02cc8272a9a020f4200e346e276ae664e45ee80745574e2f5ab80");
    bui_hex_res rhs_res = bui_from_hex("70983d692f648185febe6d6fa607630ae68649f7e6fc45b94680096c06e4fadb");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_alloc_st add_st = bui_add(&lhs_res.bui, rhs_res.bui);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, add_st);

    const char *out_hex = bui_hex(lhs_res.bui);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL("a78865c13b14ae4e25e90771b54963ee2d68c0a64d4a8ba7c6f45ee0e9daa65b", out_hex);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

int test_arithmetic_add_long_lhs(const char *name) {
    bui_hex_res lhs_res = bui_from_hex("a0a6f028580bb02cc8272a9a020f4200e346e276ae664e45ee80745574e2f5ab80");
    bui_hex_res rhs_res = bui_from_hex("70983d692f648185febe6d6fa607630ae68649f7e6fc45b94680096c06e4fadb");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_alloc_st add_st = bui_add(&lhs_res.bui, rhs_res.bui);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, add_st);

    const char *out_hex = bui_hex(lhs_res.bui);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL("a1178865c13b14ae4e25e90771b54963ee2d68c0a64d4a8ba7c6f45ee0e9daa65b", out_hex);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

int test_arithmetic_add_long_rhs(const char *name) {
    bui_hex_res lhs_res = bui_from_hex("a6f028580bb02cc8272a9a020f4200e346e276ae664e45ee80745574e2f5ab80");
    bui_hex_res rhs_res = bui_from_hex("a070983d692f648185febe6d6fa607630ae68649f7e6fc45b94680096c06e4fadb");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_alloc_st add_st = bui_add(&lhs_res.bui, rhs_res.bui);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, add_st);

    const char *out_hex = bui_hex(lhs_res.bui);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL("a1178865c13b14ae4e25e90771b54963ee2d68c0a64d4a8ba7c6f45ee0e9daa65b", out_hex);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

/* SUB ***********************************************************************/

int test_arithmetic_sub(const char *name) {
    bui_hex_res lhs_res = bui_from_hex("33ced2c76b26cae94e162c4c0d2c0ff7c13094b0185a3c122e732d5ba77efebc");
    bui_hex_res rhs_res = bui_from_hex("22e962951cb6cd2ce279ab0e2095825c141d48ef3ca9dabf253e38760b57fe03");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_sub_st sub_st = bui_sub(&lhs_res.bui, rhs_res.bui);
    TINYTEST_EQUAL(BUI_SUB_SUCCESS, sub_st);

    const char *out_hex = bui_hex(lhs_res.bui);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL("10e570324e6ffdbc6b9c813dec968d9bad134bc0dbb061530934f4e59c2700b9", out_hex);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

int test_arithmetic_sub_zero(const char *name) {
    const char *hex = "33ced2c76b26cae94e162c4c0d2c0ff7c13094b0185a3c122e732d5ba77efebc";
    bui_hex_res lhs_res = bui_from_hex(hex);
    bui_hex_res rhs_res = bui_from_hex("0");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_sub_st sub_st = bui_sub(&lhs_res.bui, rhs_res.bui);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, sub_st);

    const char *out_hex = bui_hex(lhs_res.bui);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL(hex, out_hex);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

int test_arithmetic_sub_self(const char *name) {
    const char *hex = "33ced2c76b26cae94e162c4c0d2c0ff7c13094b0185a3c122e732d5ba77efebc";
    bui_hex_res lhs_res = bui_from_hex(hex);
    bui_hex_res rhs_res = bui_from_hex(hex);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_sub_st sub_st = bui_sub(&lhs_res.bui, rhs_res.bui);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, sub_st);

    const char *out_hex = bui_hex(lhs_res.bui);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL("0", out_hex);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

int test_arithmetic_sub_short_rhs(const char *name) {
    bui_hex_res lhs_res = bui_from_hex("33ced2c76b26cae94e162c4c0d2c0ff7c13094b0185a3c122e732d5ba77efebc");
    bui_hex_res rhs_res = bui_from_hex(  "e962951cb6cd2ce279ab0e2095825c141d48ef3ca9dabf253e38760b57fe03");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_sub_st sub_st = bui_sub(&lhs_res.bui, rhs_res.bui);
    TINYTEST_EQUAL(BUI_SUB_SUCCESS, sub_st);

    const char *out_hex = bui_hex(lhs_res.bui);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL("32e570324e6ffdbc6b9c813dec968d9bad134bc0dbb061530934f4e59c2700b9", out_hex);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

int test_arithmetic_sub_long_carry(const char *name) {
    bui_hex_res lhs_res = bui_from_hex("f00000000000000000000000000000000000000ffffffffffffffff");
    bui_hex_res rhs_res = bui_from_hex("1ffffffffffffffff");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_sub_st sub_st = bui_sub(&lhs_res.bui, rhs_res.bui);
    TINYTEST_EQUAL(BUI_SUB_SUCCESS, sub_st);

    const char *out_hex = bui_hex(lhs_res.bui);
    TINYTEST_ASSERT(out_hex);
    TINYTEST_STR_EQUAL("effffffffffffffffffffffffffffffffffffff0000000000000000", out_hex);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

int test_arithmetic_sub_underflow_val(const char *name) {
    bui_hex_res lhs_res = bui_from_hex("11111111111111112222222222222222");
    bui_hex_res rhs_res = bui_from_hex("22222222222222221111111111111111");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_sub_st sub_st = bui_sub(&lhs_res.bui, rhs_res.bui);
    TINYTEST_EQUAL(BUI_SUB_UNDERFLOW, sub_st);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

int test_arithmetic_sub_underflow_len(const char *name) {
    bui_hex_res lhs_res = bui_from_hex("0");
    bui_hex_res rhs_res = bui_from_hex("11111111111111110000000000000000");
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, lhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, lhs_res.hex_st.conv_st);
    TINYTEST_EQUAL(BUI_ALLOC_SUCCESS, rhs_res.hex_st.alloc_st);
    TINYTEST_EQUAL(BUI_HEX_SUCCESS, rhs_res.hex_st.conv_st);

    bui_sub_st sub_st = bui_sub(&lhs_res.bui, rhs_res.bui);
    TINYTEST_EQUAL(BUI_SUB_UNDERFLOW, sub_st);

    bui_free(&lhs_res.bui);
    bui_free(&rhs_res.bui);

    return 1;
}

TINYTEST_START_SUITE(BuiArithmetic);
    TINYTEST_ADD_TEST(test_arithmetic_comp_less_val, NULL, NULL);
    TINYTEST_ADD_TEST(test_arithmetic_comp_less_len, NULL, NULL);
    TINYTEST_ADD_TEST(test_arithmetic_comp_eq, NULL, NULL);
    TINYTEST_ADD_TEST(test_arithmetic_comp_greater_val, NULL, NULL);
    TINYTEST_ADD_TEST(test_arithmetic_comp_greater_len, NULL, NULL);

    TINYTEST_ADD_TEST(test_arithmetic_add, NULL, NULL);
    TINYTEST_ADD_TEST(test_arithmetic_add_long_lhs, NULL, NULL);
    TINYTEST_ADD_TEST(test_arithmetic_add_long_rhs, NULL, NULL);

    TINYTEST_ADD_TEST(test_arithmetic_sub, NULL, NULL);
    TINYTEST_ADD_TEST(test_arithmetic_sub_zero, NULL, NULL);
    TINYTEST_ADD_TEST(test_arithmetic_sub_self, NULL, NULL);
    TINYTEST_ADD_TEST(test_arithmetic_sub_short_rhs, NULL, NULL);
    TINYTEST_ADD_TEST(test_arithmetic_sub_long_carry, NULL, NULL);
    TINYTEST_ADD_TEST(test_arithmetic_sub_underflow_val, NULL, NULL);
    TINYTEST_ADD_TEST(test_arithmetic_sub_underflow_len, NULL, NULL);

    /*
    TINYTEST_ADD_TEST(test_arithmetic_mul, NULL, NULL);
    TINYTEST_ADD_TEST(test_arithmetic_div_mod, NULL, NULL);
    */
TINYTEST_END_SUITE();
