#include "Unsorted/InGameFlagsUtil.hpp"

BOOL getFlagValue(u8 flagNum) {
    return (lbl_803D2D40.flags[flagNum / 8] >> (flagNum % 8)) & 1;
}

void setFlagOn(u8 flagNum) {
    lbl_803D2D40.flags[flagNum / 8] |= (1 << (flagNum % 8));
}

void setFlagOff(u8 flagNum) {
    lbl_803D2D40.flags[flagNum / 8] &= ~(1 << (flagNum % 8));
}

u32 fn_8006605C() {
    return lbl_803D2D40._1C;
}

void fn_8006606C() {
    lbl_803D2D40._9[0] += 1;
}

void fn_80066494(u8 param_1, u8 param_2) {
    lbl_803D2D40._9[param_1] = param_2;
}

// https://decomp.me/scratch/0UKNU
// This will more likely match up when the struct/object is not some global var.
void fn_80066B9C() {
    lbl_803D2D40._1008 = 0;
    lbl_803D2D40._101C = 0;
    lbl_803D2D40._100C = 0;
    lbl_803D2D40._1018 = 0;
    lbl_803D2D40._1020 = 0;
    lbl_803D2D40._1024 = 0;

    for (u32 i = 0; i < 256; i += 8) {
        for (u8 j = 0; j < 8; j++) {
            u8 flagAddr = j + i;
            lbl_803D2D40._1659[flagAddr / 8] &= ~(1 << (flagAddr % 8));
        }
    }

}
