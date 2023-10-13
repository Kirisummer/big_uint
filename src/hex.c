#include "big_uint.h"

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "ints.h"

// memory constants
static const size HEX_BLOCK_STEP = sizeof(bui_block) * 2;

// hex constants
static const u8 HEX_SHIFT = 4; // x / 16 == x >> 4;
static const u8 HEX_MASK = 15; // x % 16 == x & 0b1111

static inline bui_block from_hex(const char *begin, const char *end) {
    // converts hex number to integer
    bui_block res = 0;
    for (const char *byte = begin; byte < end; ++byte) {
        res <<= HEX_SHIFT;
        u8 mod;
        if ('0' <= *byte && *byte <= '9') {
            mod = *byte - '0';
        } else { // a-f
            mod = tolower(*byte) - 'a' + 10;
        }
        res |= mod;
    }
    return res;
}

bui_hex_st bui_set_hex(big_uint *bui, const char *str) {
    // get to the end and check digits
    const char *ptr;
    for (ptr = str; *ptr; ++ptr) {
        if (!isxdigit(*ptr)) {
            return (bui_hex_st) {
                .conv_st = BUI_HEX_INVFORMAT,
                .alloc_st = BUI_ALLOC_SUCCESS
            };
        }
    }

    // realloc blocks if needed
    // assignment to new variables allows caller to free memory on fail
    // NOTE: new blocks are not zeroed out!!!
    const size str_len = ptr - str;
    const usize req_byte_alloc = (str_len >> 1); // str_len / 2
    const usize req_block_alloc = req_byte_alloc / sizeof(bui_block)
                                + !!(req_byte_alloc % sizeof(bui_block));
    if (req_block_alloc > bui->alloc) {
        const usize new_size = sizeof(bui_block) * req_block_alloc;
        bui_block *new_ptr = realloc(bui->blocks, new_size);
        if (new_ptr) {
            bui->blocks = new_ptr;
            bui->alloc = req_block_alloc;
        } else {
            return (bui_hex_st) {
                .conv_st = BUI_HEX_SUCCESS,
                .alloc_st = BUI_ALLOC_FAIL
            };
        }
    }

    // process blocks from the end
    usize block_no = 0;
    while (ptr > str) {
        // lock end and jump ptr to the beginning of what block can capture
        // end is after the last character
        const char *end = ptr;
        ptr -= HEX_BLOCK_STEP;
        if (ptr < str) {
            // first block might be shorter
            ptr = str;
        }
        bui->blocks[block_no++] = from_hex(ptr, end);
    }
    bui->len = block_no;

    return (bui_hex_st) {
        .conv_st = BUI_HEX_SUCCESS,
        .alloc_st = BUI_ALLOC_SUCCESS
    };
}

static inline void write_hex(bui_block block, char *res) {
    // write from the least significant byte i.e. out end
    // this will be 64 / 4 (i.e. shift amount) = 16 bytes
    for (usize pos = HEX_BLOCK_STEP; pos > 0; --pos) {
        const u8 mod = block & HEX_MASK;
        block >>= HEX_SHIFT;
        if (mod < 10) {
            res[pos - 1] = '0' + mod;
        } else {
            res[pos - 1] = 'a' + (mod - 10);
        }
    }
}

char* bui_hex(const big_uint bui) {
    // (2 digits per byte) * block amount + NULL
    char *res = calloc(sizeof(char), HEX_BLOCK_STEP * bui.len + 1);
    if (!res) {
        return NULL;
    }

    // shift out forward block by block
    // loop blocks from the most significant one (the last one)
    char *block_out = res;
    bui_block *block = bui.blocks + bui.len - 1;
    while (block >= bui.blocks) {
        write_hex(*block, block_out);
        block_out += HEX_BLOCK_STEP;
        --block;
    }

    return res;
}
