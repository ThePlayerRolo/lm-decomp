#include "Koga/UnkUtil.hpp"
#include "Unsorted/80009638.hpp"

// This is the same implementation as ToolData::hashString yet it seems to be seperated here?
u32 hashStringSeperate(const char* key) {
    u32 stringHash = 0;
    char current_char;

    while ((current_char = *key) != 0) {
        key++;
        stringHash = (current_char + (stringHash << 8)) % 0x1FFFFD9;
    }
    return stringHash;
}

// Seems to take an angle and normalize it
s32 normalizeAngle(f64 x) {
    while (x < 0.0 || 360.0 < x) {
        if (x < 0.0) x += 360.0;
        if (360.0 < x) x -= 360.0;
    }

    return x * 65536.0 / 360.0;
}

f32 fn_800BA380() {
    return fn_80009638C_Modulate(10000) / 9999.0f;
}

// https://decomp.me/scratch/MlUyC
s32 fn_800BA3DC(u16 param_1, u16 param_2) {
    s32 iVar1 = param_2 - param_1;
    if (iVar1 < 0) {
        iVar1 = -iVar1;
    }

    if (iVar1 > 0x8000)
        iVar1 = 0x10000 - iVar1;

    if (param_1 < 0x8000) {
        bool bVar3 = false;
        if (param_1 < param_2 && param_2 <= param_1 + 0x8000) {
            bVar3 = true;
        }

        if (bVar3) {
            return iVar1;
        }

        return -iVar1;
    }

    bool bVar3 = false;

    if (param_1 - 0x8000 < param_2 && param_2 <= param_1) {
        bVar3 = true;
    }

    if (bVar3) {
        return -iVar1;
    }

    return iVar1;
}

// https://decomp.me/scratch/H3o1B
bool fn_800BA534(u16 param_1, u16 param_2, u16 param_3) {
    s32 iVar1 = param_1 - param_2;
    if (iVar1 < 0) {
        iVar1 = -iVar1;
    }

    if (iVar1 > 0x8000) iVar1 = 0x10000 - iVar1;

    if (iVar1 <= param_3) return true;

    return false;
}
