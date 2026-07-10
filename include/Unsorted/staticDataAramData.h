#ifndef STATIC_DATA_ARAM_DATA_H
#define STATIC_DATA_ARAM_DATA_H

#include <JSystem/JKernel/JKRAram.hpp>


class LMAramData {
public:
    inline void setAddrAndSize(JKRAramBlock* pBlock) {
        mSize = pBlock->mSize;
        mAddress = pBlock->mAddress;
    }
public:
    /* 0x00 */ u32 mAddress;
    /* 0x04 */ u32 mSize;
    /* 0x08 */ s32 _8;
    /* 0x0C */ s32 _C;
    /* 0x10 */ JKRAMCommand* mCommand;
};

extern LMAramData sGameboyAramData;
extern LMAramData sGuidemapAramData;
extern LMAramData sResTitleAramData;
extern LMAramData sResPauseAramData;
extern LMAramData sResListAramData;

#endif
