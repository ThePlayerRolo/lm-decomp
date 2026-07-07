#ifndef MOVE_OBJ_H_
#define MOVE_OBJ_H_

#include <types.h>
#include <dolphin/mtx.h>

class MoveObj {
public:
    MoveObj();

    /* 0x08 */ virtual ~MoveObj();
    /* 0x0C */ virtual void vt_0C(u16, u16, u16);

    inline s32 get_3C() const { return _3C; }
public:
    /* 0x004 */ u8 _0[0x38];
    /* 0x03C */ s32 _3C;
    /* 0x040 */ u8 _40[0x788 - 0x40];
};

#endif
