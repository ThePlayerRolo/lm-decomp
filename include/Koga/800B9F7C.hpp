#ifndef _800B9F7C_H_
#define _800B9F7C_H_

#include "JSystem/JGeometry/JGVec3.hpp"

class MoveObj;

namespace Koga {
    //Seems like a create function
    void fn_800B9F7C(s32 count);

    //Seems like a destroy function
    void fn_800BA050();

    void fn_800BA07C(s32 param_1, s32 param_2, Mtx44 param_3);

    void fn_800BA0C0(Mtx44, JGeometry::TVec3f*, JGeometry::TVec3f*, Mtx44);

    // Returns the count of the lbl_804D8C50 and lbl_804D8C54 arrays and sets the dst parameter to lbl_804D8C50
    s32 fn_800BA184(Mtx44** dst);

    bool fn_800BA194(Mtx44 param_1, MoveObj* pObj);

    //Returns a value from lbl_804D8C54
    u8 fn_800BA210(s32 idx);

    //Set two values in the lbl_804D8C54 array to 1
    void fn_800BA21C(u32 param_1);

    //Set two values in the lbl_804D8C54 array to 0
    void fn_800BA278(u32 param_1);
}


#endif
