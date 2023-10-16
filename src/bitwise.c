#include "big_uint.h"

#include <stdbool.h>

#include "utils.h"

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

    for (size_t pos = 0; pos < rhs.len; ++pos) {
        lhs->blocks[pos] ^= rhs.blocks[pos];
    }
    return BUI_ALLOC_SUCCESS;
}

bui_alloc_st bui_or(big_uint *lhs, const big_uint rhs) {
    if (lhs->alloc < rhs.len) {
        bui_alloc_st realloc_st = bui_realloc(lhs, rhs.len);
        if (realloc_st != BUI_ALLOC_SUCCESS) {
            return realloc_st;
        }
    }

    for (size_t pos = 0; pos < rhs.len; ++pos) {
        lhs->blocks[pos] |= rhs.blocks[pos];
    }

    return BUI_ALLOC_SUCCESS;
}

void bui_and(big_uint *lhs, const big_uint rhs) {
    const size_t min_len = (lhs->len < rhs.len)? lhs->len: rhs.len;
    size_t pos;

    // apply & rhs to each lhs block
    for (pos = 0; pos < rhs.len; ++pos) {
        lhs->blocks[pos] &= rhs.blocks[pos];
    }
    // zero out the rest since rest of operations are essentially & 0
    for (; pos < lhs->len; ++pos) {
        lhs->blocks[pos] = 0;
    }
}

void bui_shr(big_uint *bui, uintmax_t amount) {
    const uint8_t block_bits = sizeof(bui_block) * 8;
    const uintmax_t full_blocks = amount / block_bits;
    const uint8_t shift = amount % block_bits;
    const uint8_t rev_shift = block_bits - shift;

    /*
     *      3    2    1    0    : block no
     *     (1234 5678 9012 3456) >> 11, block size is 4 digits ("bits")
     *  1. full_blocks = 11 / 4 = 2, shift = 11 % 4 = 3, rev_shift = 4 - 3 = 1
     *  2. (1234 5678 ---- ----): two blocks are ignored and will be overwritten
     *  3. (1234 5678 ---- ---5): shifted = 5, carry = 678. No block to put carry in
     *  4. (1234 5678 ---1 2345): shifted = 1, carry = 234. Carry put in block 3 - full_blocks - 1 = 0
     *  5. Most sign. block (len - full_blocks - 1) = 1 is not zero, not put to allocation reserve
     *  6. (xxxx xxxx ---1 2345): set len to 4 - full_blocks = 2
     *
     *      2    1    0    : block no
     *     (-123 4567 8901) >> 3, block size is 4 digits ("bits")
     *  1. full_blocks = 3 / 4 = 0, shift = 3 % 4 = 3, rev_shift = 4 - 3 = 1
     *  1. (-123 4567 ---8): shifted = 8, carry = 901. No block to put carry in
     *  2. (-123 ---4 5678): shifted = 4, carry = 567. Carry put in block 1 - 0 - 1 = 0
     *  3. (---- 1234 5678): shifted = -, carry = 123. Carry put in block 2 - 0 - 1 = 1
     *  4. Most sign. block (3 - 0 - 1) = 2 is zero, put to allocation reserve
     *  5. (xxxx 1234 5678): set len to 3 - 0 - 1 (block 2) = 2
     */

    for (size_t pos = full_blocks; pos < bui->len; ++pos) {
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

bui_alloc_st bui_shl(big_uint *bui, uintmax_t amount) {
    const uint8_t block_bits = sizeof(bui_block) * 8;
    const size_t full_blocks = amount / block_bits;
    const uint8_t shift = amount % block_bits;
    const uint8_t rev_shift = block_bits - shift;

    // check if most sign. block will be shifted to the unexisting block
    const bool msb_has_carry = bui->blocks[bui->len - 1] >> rev_shift;
    const size_t new_alloc = full_blocks + msb_has_carry;

    if (new_alloc) {
        bui_alloc_st realloc_st = bui_realloc(bui, bui->len + new_alloc);
        if (realloc_st != BUI_ALLOC_SUCCESS) {
            return realloc_st;
        }
    }

    for (size_t i = bui->len; i > 0; --i) {
        const size_t pos = i - 1;
        const bui_block shifted = bui->blocks[pos] << shift;
        const bui_block carry = bui->blocks[pos] >> rev_shift;

        bui->blocks[pos] = 0;
        bui->blocks[pos + full_blocks] = shifted;

        const size_t carry_block = pos + full_blocks + 1;
        if (carry_block < bui->alloc) {
            bui->blocks[carry_block] |= carry;
        }
    }

    bui->len = bui->len + new_alloc;

    return BUI_ALLOC_SUCCESS;
}
