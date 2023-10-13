#include "big_uint.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "ints.h"

bui_alloc_res bui_copy(const big_uint other) {
    bui_alloc_res res;
    if (!other.blocks) {
        res.alloc_st = BUI_ALLOC_FAIL;
        return res;
    }

    const usize buf_size = sizeof(bui_block) * other.len;
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
    bui_alloc_res res;
    res.bui.blocks = malloc(sizeof(bui_block));
    res.bui.alloc = res.bui.len = 1;

    if (res.bui.blocks) {
        *res.bui.blocks = u;
    } else {
        res.alloc_st = BUI_ALLOC_FAIL;
    }
    return res;
}

void bui_free(big_uint *bui) {
    free(bui->blocks);
    bui->blocks = NULL;
    bui->len = 0;
    bui->alloc = 0;
}
