#include "Unsorted/character.hpp"
#include "Koga/800B9F7C.hpp"

extern void fn_8001B31C(u8, u8*, u8*);
extern bool fn_800E9ED0(s32);
extern void fn_80097B24(Mtx*, MoveObj*, s32);

extern JGeometry::TVec3f lbl_802FFA88[2];
extern Mtx44* lbl_804D8C50;
extern bool* lbl_804D8C54;
extern s32 lbl_804D8C58;

namespace Koga {

    //https://decomp.me/scratch/HsTFB
    void fn_800B9F7C(s32 count) {
        lbl_804D8C58 = count;

        if (count > 0) {
            lbl_804D8C50 = new Mtx44[count];
            lbl_804D8C54 = new bool[count];

            //Some initalization code....
        }
    }

    void fn_800BA050() {
        delete[]  lbl_804D8C50;
        delete[] lbl_804D8C54;
    }

    //https://decomp.me/scratch/UvgTC
    void fn_800BA07C(s32 param_1, s32 param_2, Mtx44 param_3) {
        Mtx44* val = &lbl_804D8C50[param_1];

        Vec* val_1 = &lbl_802FFA88[param_2];

        fn_800BA0C0(*val, &lbl_802FFA88[param_2], &lbl_802FFA88[1], param_3);
    }


    void fn_800BA0C0(Mtx44 dst, JGeometry::TVec3f* param_2, JGeometry::TVec3f* param_3, Mtx44 param_4) {
        Vec local_20;
        PSMTXMultVec(param_4, param_2, &local_20);
        dst[0][1] = local_20.x;
        dst[0][2] = local_20.y;
        dst[0][3] = local_20.z;
        dst[1][0] = param_4[0][2];
        dst[1][1] = param_4[1][2];
        dst[1][2] = param_4[2][2];
        dst[2][0] = param_4[0][1];
        dst[2][1] = param_4[1][1];
        dst[2][2] = param_4[2][1];
        dst[3][0] = param_4[0][0];
        dst[3][1] = param_4[1][0];
        dst[3][2] = param_4[2][0];

        dst[1][3] = param_3->z;
        dst[2][3] = param_3->y;
        dst[3][3] = param_3->x;
    }

    s32 fn_800BA184(Mtx44** dst) {
        *dst = lbl_804D8C50;
        return lbl_804D8C58;
    }


    bool fn_800BA194(Mtx44 param_1, MoveObj* pObj) {

        if (!fn_800E9ED0(pObj->get_3C())) return false;
        Mtx stack_38;

        fn_80097B24(&stack_38, pObj, 0);
        // TODO: This casting feels fakey
        fn_800BA0C0(param_1, &lbl_802FFA88[0], &lbl_802FFA88[1], *(Mtx44*)stack_38);

        return true;
    }

    //Inline used for stack matching
    void set_lbl_804D8C54(s32 idx, bool val) {
        lbl_804D8C54[idx] = val;
    }

    u8 fn_800BA210(s32 idx) {
        return lbl_804D8C54[idx];
    }

    void fn_800BA21C(u32 param_1) {
        u8 local_10;
        u8 local_11;

        fn_8001B31C(param_1, &local_10, &local_11);

        if (local_10 != 0xFF) {
            set_lbl_804D8C54(local_10, true);
        }
        if (local_11 != 0xFF) {
            lbl_804D8C54[local_11] = true;
        }
    };

    void fn_800BA278(u32 param_1) {
        u8 local_10;
        u8 local_11;

        fn_8001B31C(param_1, &local_10, &local_11);

        if (local_10 != 0xFF) {
            set_lbl_804D8C54(local_10, false);
        }
        if (local_11 != 0xFF) {
            lbl_804D8C54[local_11] = false;
        }
    };

}
