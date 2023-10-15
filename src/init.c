#include "big_uint.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

bui_alloc_res bui_copy(const big_uint other) {
    bui_alloc_res res = {0};
    if (!other.blocks) {
        res.alloc_st = BUI_ALLOC_FAIL;
        return res;
    }

    const size_t buf_size = sizeof(bui_block) * other.len;
    res.bui.blocks = malloc(buf_size);
    if (!res.bui.blocks) {
        res.alloc_st = BUI_ALLOC_FAIL;
        return res;
    }
    memcpy(res.bui.blocks, other.blocks, buf_size);
    res.bui.len = res.bui.alloc = other.len;
    res.alloc_st = BUI_ALLOC_SUCCESS;
    return res;
}

bui_hex_res bui_from_hex(const char *str) {
    bui_hex_res res = {0};
    res.hex_st = bui_set_hex(&res.bui, str);
    return res;
}

bui_alloc_res bui_from_uint(const bui_block u) {
    bui_alloc_res res = {0};
    res.alloc_st = bui_set_uint(&res.bui, u);
    return res;
}

bui_alloc_st bui_set_uint(big_uint *bui, const bui_block u) {
    if (!bui->alloc) {
        bui->blocks = malloc(sizeof(bui_block));
        if (bui->blocks) {
            bui->alloc = 1;
        } else {
            return BUI_ALLOC_FAIL;
        }
    }

    *bui->blocks = u;
    bui->len = 1;

    return BUI_ALLOC_SUCCESS;
}

void bui_free(big_uint *bui) {
    free(bui->blocks);
    bui->blocks = NULL;
    bui->len = 0;
    bui->alloc = 0;
}
