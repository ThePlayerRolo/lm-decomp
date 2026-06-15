#include "Unsorted/InGameFlagsUtil.hpp"

BOOL getFlagValue(u8 flagNum) {
    return (sUnkStruct.flags[flagNum / 8] >> (flagNum % 8)) & 1;
}

void setFlagOn(u8 flagNum) {
    sUnkStruct.flags[flagNum / 8] |= (1 << (flagNum % 8));
}

void setFlagOff(u8 flagNum) {
    sUnkStruct.flags[flagNum / 8] &= ~(1 << (flagNum % 8));
}

u32 fn_8006605C() {
    return sUnkStruct.unk2;
}

void fn_8006606C() {
    sUnkStruct.unk1[0] += 1;
}

void fn_80066494(u8 param_1, u8 param_2) {
    sUnkStruct.unk1[param_1] = param_2;
}

// https://decomp.me/scratch/0UKNU
// This will more likely match up when the struct/object is not some global var.
void fn_80066B9C() {
    sUnkStruct._1008 = 0;
    sUnkStruct._101C = 0;
    sUnkStruct._100C = 0;
    sUnkStruct._1018 = 0;
    sUnkStruct._1020 = 0;
    sUnkStruct._1024 = 0;

    for (u32 i = 0; i < 256; i += 8) {
        for (u8 j = 0; j < 8; j++) {
            u8 flagAddr = j + i;
            sUnkStruct._1659[flagAddr / 8] &= ~(1 << (flagAddr % 8));
        }
    }

}
