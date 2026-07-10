#ifndef _80008418_H_
#define _80008418_H_

#include "dolphin/mtx.h"
#include <types.h>

class unk_lbl_803A3820 {

public:
    /* 0x000 */ u8 pad[0x18C];
    /* 0x18C */ Mtx _18C;
    /* 0x1BC */ u8 pad2[0x260 - 0x1BC];
};

void fn_80008654(unk_lbl_803A3820*);
extern unk_lbl_803A3820 lbl_803A3820;


#endif
