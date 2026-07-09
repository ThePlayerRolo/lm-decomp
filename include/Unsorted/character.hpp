#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Unsorted/MoveObj.hpp"
#include <JSystem/JGeometry/JGVec3.hpp>

class Character : public MoveObj {
public:
    Character();

    /* 0x08 */ virtual ~Character();
    /* 0x10 */ virtual void vt_10();
    /* 0x14 */ virtual void vt_14();
    /* 0x18 */ virtual void vt_18();
    /* 0x1C */ virtual s32 vt_1C();
    /* 0x20 */ virtual void vt_20(JGeometry::TVec3f*);
    /* 0x24 */ virtual void vt_24(void*); // Unsure of arg type.

public:
    /* 0x78C */ s32 _78C;
};

// All of these are referenced in EnManager. No arg types or return types are guaranteed.
void characterInit(void*, void*); // lbl_8033B1B0 = character.cpp,  lbl_8033B1C0 = Character init failed
void* fn_80069130(void*);

#endif
