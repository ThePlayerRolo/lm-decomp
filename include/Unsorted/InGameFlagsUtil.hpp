#ifndef INGAME_FLAGS_UTIL_HPP
#define INGAME_FLAGS_UTIL_HPP

#include "types.h"

struct unkStruct {
    u8 _0[0x9];
    u8 unk1[0x12];
    u32 unk2;
    u8 _30[0x639]; // TODO figure out what this is

    // Every flag is a single bit
    // Flags 0-84 are savable in the mem card
    // Flags 85-169 are reset back to off/0 every time Luigi leaves the room
    // Flags 170-255 are reset back to off/0 every time Luigi changes Maps.
    u8 flags[0x20];

    u8 _683[0x98F];
    u8 _1008;
    u8 _1009[0x3];
    u32 _100C;
    u8 _1010[0x8];
    u32 _1018;
    u32 _101C;
    u32 _1020;
    u32 _1024;
    u8 _1028[0x631];
    u8 _1659[0x20];
};

extern "C" unkStruct sUnkStruct;

int getFlagValue(int);
void setFlagOn(int);
void setFlagOff(int);
u32 fn_8006605C();
void fn_8006606C();
void fn_80066084();
void fn_8006628C();
void fn_80066494(int, u8);
void fn_800664AC(int);
void fn_80066730(int*);
void fn_80066C9C();


#endif
