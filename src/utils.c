#include "utils.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

bui_alloc_st bui_realloc(big_uint *bui, size_t new_alloc) {
    bui_block *new_ptr = realloc(bui->blocks, sizeof(bui_block) * new_alloc);
    if (new_ptr) {
        if (bui->alloc < new_alloc) {
            const size_t new_blocks = new_alloc - bui->alloc;
            memset(new_ptr + bui->alloc, 0, new_blocks);
        }
        bui->blocks = new_ptr;
        bui->alloc = new_alloc;
        return BUI_ALLOC_SUCCESS;
    } else {
        return BUI_ALLOC_FAIL;
    }
}
