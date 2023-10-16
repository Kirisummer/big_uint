#ifndef KIRISUMMER_BIGINT_H_
#define KIRISUMMER_BIGINT_H_

#include <stdint.h>
#include <stddef.h>

#define BUI_BLOCK_MAX UINT64_MAX
typedef uint64_t bui_block;

typedef struct big_uint {
    // least significant block first (small-endian but for blocks)
    bui_block *blocks;
    size_t len;
    size_t alloc;
} big_uint;

/* Inits, sets and gets *****************************************/

typedef enum bui_alloc_st {
    BUI_ALLOC_SUCCESS = 0,
    BUI_ALLOC_FAIL,
} bui_alloc_st;

typedef struct bui_alloc_res {
    big_uint bui;
    bui_alloc_st alloc_st;
} bui_alloc_res;

bui_alloc_res bui_copy(const big_uint other);
void bui_free(big_uint *bui);

typedef enum bui_hex_conv_st {
    BUI_HEX_SUCCESS = 0,
    BUI_HEX_INVFORMAT,
} bui_hex_conv_st;

typedef struct bui_hex_st {
    bui_hex_conv_st conv_st;
    bui_alloc_st alloc_st;
} bui_hex_st;

typedef struct bui_hex_res {
    big_uint bui;
    bui_hex_st hex_st;
} bui_hex_res;

bui_hex_res bui_from_hex(const char *str);
bui_hex_st bui_set_hex(big_uint *bui, const char *str);
char* bui_hex(const big_uint bui);

bui_alloc_res bui_from_uint(const bui_block u);
bui_alloc_st bui_set_uint(big_uint *bui, const bui_block u);

/* Bitwise ops ***************************************************************/
void bui_inv(big_uint *bui);
bui_alloc_st bui_xor(big_uint *lhs, const big_uint rhs);
bui_alloc_st bui_or(big_uint *lhs, const big_uint rhs);
void bui_and(big_uint *lhs, const big_uint rhs);
void bui_shr(big_uint *bui, uintmax_t amount); // >>
bui_alloc_st bui_shl(big_uint *bui, uintmax_t amount); // <<

/* Arithmetic ops ************************************************************/
typedef enum bui_comp_res {
    BUI_COMP_LS = 1, // 0b001
    BUI_COMP_EQ = 2, // 0b010
    BUI_COMP_GT = 4, // 0b100
} bui_comp_res;

bui_comp_res bui_comp(const big_uint lhs, const big_uint rhs);

bui_alloc_st bui_add(big_uint* lhs, const big_uint rhs);

typedef enum bui_sub_st {
    BUI_SUB_SUCCESS = 0,
    BUI_SUB_UNDERFLOW,
} bui_sub_st;

bui_sub_st bui_sub(big_uint *lhs, const big_uint rhs);

bui_alloc_res bui_mul(const big_uint lhs, const big_uint rhs);

typedef enum bui_div_st {
    BUI_DIV_SUCCESS = 0,
    BUI_DIV_ZERO,
} bui_div_st;

typedef struct bui_div_res {
    big_uint div;
    big_uint mod;

    bui_alloc_st alloc_st;
    bui_div_st div_st;
} bui_div_res;

bui_div_res bui_div_mod(const big_uint lhs, const big_uint rhs);

#endif // KIRISUMMER_BIGINT_H_
