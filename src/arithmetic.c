#include "big_uint.h"

#include <assert.h>
#include <stdbool.h>

#include "utils.h"

bui_comp_res bui_comp(const big_uint lhs, const big_uint rhs) {
    if (lhs.len < rhs.len) {
        return BUI_COMP_LS;
    } else if (lhs.len > rhs.len) {
        return BUI_COMP_GT;
    }

    for (size_t i = lhs.len; i > 0; --i) {
        const size_t pos = i - 1;
        if (lhs.blocks[pos] < rhs.blocks[pos]) {
            return BUI_COMP_LS;
        } else if (lhs.blocks[pos] > rhs.blocks[pos]) {
            return BUI_COMP_GT;
        }
    }
    
    return BUI_COMP_EQ;
}

bui_alloc_st bui_add(big_uint* lhs, const big_uint rhs) {
    size_t min_len, max_len;
    const big_uint *longest;
    if (lhs->len < rhs.len) {
        min_len = lhs->len;
        max_len = rhs.len;
        longest = &rhs;
    } else {
        min_len = rhs.len;
        max_len = lhs->len;
        longest = lhs;
    }

    // Realloc one excess byte for possible carry. We don't want to realloc twice
    if (max_len >= lhs->alloc) {
        bui_alloc_st realloc_st = bui_realloc(lhs, max_len + 1);
        if (realloc_st != BUI_ALLOC_SUCCESS) {
            return realloc_st;
        }
    }

    // Handle blocks that are present in both args
    bool carry = false;
    for (size_t pos = 0; pos < min_len; ++pos) {
        bui_block new_value = lhs->blocks[pos] + rhs.blocks[pos];
        // carry will be present if lhs + rhs overflows
        // OR lhs + rhs is the maximum value a block can hold and carry is present
        bool new_carry = (new_value < lhs->blocks[pos])
                      || (carry && new_value == BUI_BLOCK_MAX);
        new_value += carry;

        lhs->blocks[pos] = new_value;
        carry = new_carry;
    }

    // Handle blocks from longer arg
    for (size_t pos = min_len; pos < max_len; ++pos) {
        lhs->blocks[pos] = longest->blocks[pos] + carry;
        // block overflow check
        carry = (lhs->blocks[pos] == 0);
    }
    lhs->len = max_len;

    // Add a block if there's carry
    if (carry) {
        lhs->blocks[++lhs->len] = 1;
    }

    return BUI_ALLOC_SUCCESS;
}

bui_sub_st bui_sub(big_uint *lhs, const big_uint rhs) {
    // check args FULLY to prevent "partial" subtraction
    // and save some time on safety checks later
    if (bui_comp(*lhs, rhs) == BUI_COMP_LS) {
        return BUI_SUB_UNDERFLOW;
    }

    bool carry = false;
    for (size_t pos = 0; pos < rhs.len; ++pos) {
        if (carry) {
            lhs->blocks[pos] -= carry;
            carry = (lhs->blocks[pos] == BUI_BLOCK_MAX); // underflow
        } else {
            carry = (lhs->blocks[pos] < rhs.blocks[pos]);
        }
        lhs->blocks[pos] -= rhs.blocks[pos];
    }

    // get rid of carry
    for (size_t pos = rhs.len; carry; ++pos) {
        assert(pos < lhs->len);

        --lhs->blocks[pos];
        carry = (lhs->blocks[pos] == BUI_BLOCK_MAX); // underflow
    }

    // find most sign. non-zero block
    size_t new_len = lhs->len;
    while (new_len > 0 && !lhs->blocks[new_len - 1]) {
        --new_len;
    }
    lhs->len = new_len;

    return BUI_SUB_SUCCESS;
}
