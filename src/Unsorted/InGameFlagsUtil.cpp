#include "Unsorted/InGameFlagsUtil.hpp"

int getFlagValue(int flagNum) {
    int maskedFlag = flagNum & 0xFF;
    return (sUnkStruct.flags[maskedFlag / 8] >> (maskedFlag % 8)) & 1;
}

void setFlagOn(int flagNum) {
    int maskedFlag = flagNum & 0xFF;
    sUnkStruct.flags[maskedFlag / 8] |= 1 << (maskedFlag % 8);
}

void setFlagOff(int flagNum) {
    int maskedFlag = flagNum & 0xFF;
    sUnkStruct.flags[maskedFlag / 8] &= ~(1 << (maskedFlag % 8));
}

u32 fn_8006605C() {
    return sUnkStruct.unk2;
}

void fn_8006606C() {
    sUnkStruct.unk1[0] += 1;
}

void fn_80066494(int param_1, u8 param_2) {
    sUnkStruct.unk1[param_1 & 0xFF] = param_2;
}

//https://decomp.me/scratch/0UKNU
// Should be higher but the instructions are shifted for some reason.
void fn_80066B9C() {
    sUnkStruct._1008 = 0;
    sUnkStruct._101C = 0;
    sUnkStruct._100C = 0;
    sUnkStruct._1018 = 0;
    sUnkStruct._1020 = 0;
    sUnkStruct._1024 = 0;

    for (int i = 0; i < 32; i += 8) {
        int flagAddr = i & 0xFF;
        sUnkStruct._1659[flagAddr / 8] &= ~(1 << (flagAddr % 8));

        flagAddr = (i + 1) & 0xFF;
        sUnkStruct._1659[flagAddr / 8] &= ~(1 << (flagAddr % 8));
        
        flagAddr = (i + 2) & 0xFF;
        sUnkStruct._1659[flagAddr / 8] &= ~(1 << (flagAddr % 8));

        flagAddr = (i + 3) & 0xFF;
        sUnkStruct._1659[flagAddr / 8] &= ~(1 << (flagAddr % 8));
        
        flagAddr = (i + 4) & 0xFF;
        sUnkStruct._1659[flagAddr / 8] &= ~(1 << (flagAddr % 8));
        
        flagAddr = (i + 5) & 0xFF;
        sUnkStruct._1659[flagAddr/ 8] &= ~(1 << (flagAddr % 8));
        
        flagAddr = (i + 6) & 0xFF;
        sUnkStruct._1659[flagAddr / 8] &= ~(1 << (flagAddr % 8));
        
        flagAddr = (i + 7) & 0xFF;
        sUnkStruct._1659[flagAddr / 8] &= ~(1 << (flagAddr % 8));
    }
}
