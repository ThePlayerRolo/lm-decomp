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

public:
    /* 0x78C */ s32 _78C;
};

#endif
