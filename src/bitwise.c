#include "big_uint.h"

#include <stdlib.h>
#include <string.h>

static inline bui_alloc_st bui_realloc(big_uint *bui, usize new_alloc) {
    bui_block *new_ptr = realloc(bui->blocks, sizeof(bui_block) * new_alloc);
    if (new_ptr) {
        if (bui->alloc < new_alloc) {
            const usize new_blocks = new_alloc - bui->alloc;
            memset(new_ptr + bui->alloc, 0, new_blocks);
        }
        bui->blocks = new_ptr;
        bui->alloc = new_alloc;
        return BUI_ALLOC_SUCCESS;
    } else {
        return BUI_ALLOC_FAIL;
    }
}

void bui_inv(big_uint *bui) {
    bui_block *end = bui->blocks + bui->len;
    for (bui_block *block = bui->blocks; block < end; ++block) {
        *block = ~*block;
    }
}

bui_alloc_st bui_xor(big_uint *lhs, const big_uint rhs) {
    if (lhs->alloc < rhs.len) {
        bui_alloc_st realloc_st = bui_realloc(lhs, rhs.len);
        if (realloc_st != BUI_ALLOC_SUCCESS) {
            return realloc_st;
        }
    }

    for (usize pos = 0; pos < rhs.len; ++pos) {
        lhs->blocks[pos] ^= rhs.blocks[pos];
    }
}

bui_alloc_st bui_or(big_uint *lhs, const big_uint rhs) {
    if (lhs->alloc < rhs.len) {
        bui_alloc_st realloc_st = bui_realloc(lhs, rhs.len);
        if (realloc_st != BUI_ALLOC_SUCCESS) {
            return realloc_st;
        }
    }

    for (usize pos = 0; pos < rhs.len; ++pos) {
        lhs->blocks[pos] |= rhs.blocks[pos];
    }
}

void bui_and(big_uint *lhs, const big_uint rhs) {
    for (usize pos = 0; pos < rhs.len; ++pos) {
        lhs->blocks[pos] &= rhs.blocks[pos];
    }
}

void bui_shr(big_uint *bui, umax amount) {
    const umax full_blocks = amount >> 3; // amount / 8
    const u8 shift = amount & 7; // amount % 8 == amount & 0b111
    const u8 rev_shift = sizeof(bui_block) * 8 - shift;

    /*
     *      3    2    1    0    : block no
     *     (1234 5678 9012 3456) >> 11, block size is 4 digits
     *  1. full_blocks = 11 / 4 = 2, shift = 11 % 4 = 3, rev_shift = 4 - 3 = 1
     *  2. (1234 5678 ---- ----): two blocks are ignored and will be overwritten
     *  3. (1234 5678 ---- ---5): shifted = 5, carry = 678. No block to put carry in
     *  4. (1234 5678 ---1 2345): shifted = 1, carry = 234. Carry put in block 3 - full_blocks - 1 = 0
     *  5. Most sign. block (len - full_blocks - 1) = 1 is not zero, not put to allocation reserve
     *  6. (xxxx xxxx ---1 2345): set len to 4 - full_blocks = 2
     *
     *      2    1    0    : block no
     *     (-123 4567 8901) >> 3, block size is 4 digits
     *  1. full_blocks = 3 / 4 = 0, shift = 3 % 4 = 3, rev_shift = 4 - 3 = 1
     *  1. (-123 4567 ---8): shifted = 8, carry = 901. No block to put carry in
     *  2. (-123 ---4 5678): shifted = 4, carry = 567. Carry put in block 1 - 0 - 1 = 0
     *  3. (---- 1234 5678): shifted = -, carry = 123. Carry put in block 2 - 0 - 1 = 1
     *  4. Most sign. block (3 - 0 - 1) = 2 is zero, put to allocation reserve
     *  5. (xxxx 1234 5678): set len to 3 - 0 - 1 (block 2) = 2
     */

    for (usize pos = full_blocks; pos < bui->len; ++pos) {
        const bui_block shifted = bui->blocks[pos] >> shift;
        // get carry in advance in case shited is put in the same block
        const bui_block carry = bui->blocks[pos] << rev_shift;

        // fully shifted blocks are overwritten by partially shifted blocks before
        bui->blocks[pos - full_blocks] = shifted;
        // if there is an overwritten block before, add carry there
        if (pos > full_blocks) {
            bui->blocks[pos - full_blocks - 1] |= carry;
        }
    }

    // We have (full_blocks) blocks that were shifted to previous blocks
    // and weren't overwritten by other blocks + possibly an empty front block
    // Unallocating these blocks will require full reallocation and copy, so it's better
    // to leave them allocated and zeroed
    const bool msb_zero = !bui->blocks[bui->len - full_blocks - 1];
    bui->len = bui->len - full_blocks - msb_zero;
}

bui_alloc_st bui_shl(big_uint *bui, umax amount) {
    const umax full_blocks = amount >> 3; // amount / 8
    const u8 shift = amount & 7; // amount % 8 == amount & 0b111
    const u8 rev_shift = sizeof(bui_block) * 8 - shift;

    // check if most sign. block will be shifted to the unexisting block
    const bool msb_has_carry = bui->blocks[bui->len - 1] >> rev_shift;
    const umax new_alloc = full_blocks + msb_has_carry;

    if (new_alloc) {
        bui_alloc_st realloc_st = bui_realloc(bui, bui->len + new_alloc);
        if (realloc_st != BUI_ALLOC_SUCCESS) {
            return realloc_st;
        }
    }

    for (usize pos = bui->len - 1; pos >= 0; --pos) {
        const bui_block shifted = bui->blocks[pos] << shift;
        const bui_block carry = bui->blocks[pos] >> rev_shift;

        bui->blocks[pos + full_blocks - 1] = shifted;
        if (pos + full_blocks < bui->alloc) {
            bui->blocks[pos + full_blocks] |= carry;
        }
    }

    return BUI_ALLOC_SUCCESS;
}
