#ifndef _LM_DVD_FILE_BLOCK_H_
#define _LM_DVD_FILE_BLOCK_H_

#include <types.h>

class LMDvdFileInfoBlock {
public:
    void fn_800071D0(LMDvdFileInfoBlock*);
    s32 size();
public:
    /* 0x0 */ u32 _0;
    /* 0x4 */ u32 mLength;
};

#endif
