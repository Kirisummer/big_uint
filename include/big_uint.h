#ifndef KIRISUMMER_BIGINT_H_
#define KIRISUMMER_BIGINT_H_

#include <stdbool.h>

#include "ints.h"

typedef umax bui_block;

typedef struct big_uint {
    // least significant block first (small-endian but for blocks)
    bui_block *blocks;
    usize len;
    usize alloc;
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

bui_alloc_res bui_from_uint(const umax u);

/* Bitwise ops ***************************************************************/
void bui_inv(big_uint *bui);
bui_alloc_st bui_xor(big_uint *lhs, const big_uint rhs);
bui_alloc_st bui_or(big_uint *lhs, const big_uint rhs);
void bui_and(big_uint *lhs, const big_uint rhs);
void bui_shr(big_uint *bui, umax amount); // >>
bui_alloc_st bui_shl(big_uint *bui, umax amount); // <<

/* Arithmetic ops ************************************************************/
bui_alloc_st bui_add(big_uint* lhs, const big_uint rhs);

typedef enum bui_sub_val_st {
    BUI_SUB_SUCCESS = 0,
    BUI_SUB_UNDERFLOW,
} bui_sub_val_st;

typedef struct bui_sub_st {
    bui_sub_val_st sub_st;
    bui_alloc_st alloc_st;
} bui_sub_st;

bui_sub_st bui_sub(big_uint* lhs, const big_uint rhs);

bui_alloc_res bui_mul(const big_uint lhs, const big_uint rhs);

typedef struct bui_div_mod_res {
    big_uint div;
    big_uint mod;
    bui_alloc_st status;
} bui_div_mod_res;
bui_div_mod_res bui_div_mod(const big_uint lhs, const big_uint rhs);

#endif // KIRISUMMER_BIGINT_H_
