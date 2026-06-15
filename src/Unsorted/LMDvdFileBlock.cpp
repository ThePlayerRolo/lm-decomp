#include "Unsorted/LMDvdFileBlock.hpp"

s32 LMDvdFileInfoBlock::fn_800071C0() {
    return mLength + 0x1F & 0xFFFFFFE0;
}

// LMDvdFileInfoBlock::fn_800071D0
