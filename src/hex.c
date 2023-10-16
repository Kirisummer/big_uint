#include "big_uint.h"

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// memory constants
static const size_t HEX_BLOCK_STEP = sizeof(bui_block) * 2;

// hex constants
static const uint8_t HEX_SHIFT = 4; // x / 16 == x >> 4;
static const uint8_t HEX_MASK = 15; // x % 16 == x & 0b1111

static inline bui_block from_hex(const char *begin, const char *end) {
    // converts hex number to integer
    bui_block res = 0;
    for (const char *byte = begin; byte < end; ++byte) {
        res <<= HEX_SHIFT;
        uint8_t mod;
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
    const size_t str_len = ptr - str;
    const size_t req_byte_alloc = (str_len >> 1) + (str_len & 1); // str_len / 2 + str_len % 2
    const size_t req_block_alloc = req_byte_alloc / sizeof(bui_block)
                                + !!(req_byte_alloc % sizeof(bui_block));
    if (req_block_alloc > bui->alloc) {
        const size_t new_size = sizeof(bui_block) * req_block_alloc;
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
    size_t block_no = 0;
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
    for (size_t pos = HEX_BLOCK_STEP; pos > 0; --pos) {
        const uint8_t mod = block & HEX_MASK;
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
    const size_t init_out_len = HEX_BLOCK_STEP * bui.len + 1;
    char *hex_out = malloc(sizeof(char) * init_out_len);
    if (!hex_out) {
        return NULL;
    }

    // shift out forward block by block
    // loop blocks from the most significant one (the last one)
    char *block_out = hex_out;
    bui_block *block = bui.blocks + bui.len - 1;
    while (block >= bui.blocks) {
        write_hex(*block, block_out);
        block_out += HEX_BLOCK_STEP;
        --block;
    }
    hex_out[init_out_len - 1] = '\0';

    // remove significant zeroes
    char *non_zero;
    for (non_zero = hex_out; *non_zero && *non_zero == '0'; ++non_zero);

    if (non_zero == hex_out) {
        // NOP
    } if (*non_zero) {
        const size_t new_size = init_out_len - (non_zero - hex_out);
        char *new_out = malloc(sizeof(char) * new_size);
        if (new_out) {
            memcpy(new_out, non_zero, new_size);
        }
        free(hex_out);
        hex_out = new_out;
    } else { // all zeroes
        free(hex_out);
        char *new_out = malloc(sizeof(char) * 2);
        if (new_out) {
            new_out[0] = '0';
            new_out[1] = '\0';
        }
        hex_out = new_out;
    }

    return hex_out;
}
