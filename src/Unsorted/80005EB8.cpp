#include "Unsorted/80005EB8.hpp"
#include <dolphin.h>
#include <JSystem/JKernel/JKRExpHeap.hpp>

static JKRExpHeap* sRootHeap;
JKRExpHeap* lbl_804D8014;
static JKRExpHeap* lbl_804D8018;
JKRExpHeap* lbl_804D801C;
static void* sGXBaseBuffer;
static GXFifoObj* sGXInitFifoObj;

static u8 sCurHeapGroupId = 1;

void initializeGX() {
    get_lbl_804D8014()->changeGroupID(1);
    sGXBaseBuffer = JKRAllocFromSysHeap( 0x80000, 0x20);
    sGXInitFifoObj = GXInit(sGXBaseBuffer,  0x80000);
}

//https://decomp.me/scratch/RvI1x
void fn_80005F10() {
    sRootHeap = JKRExpHeap::createRoot(1, false);
    s32 size = sRootHeap->getFreeSize();
    void* addr = sRootHeap->alloc(size, 4);

    //Some struct copying code....

    DCStoreRange(addr, size);
    JKRFree(addr);
    lbl_804D8014 = JKRExpHeap::create(0x6ac000, sRootHeap, false);
    lbl_804D8018 = JKRExpHeap::create(sRootHeap->getFreeSize(), nullptr, false);

    get_lbl_804D8014()->becomeSystemHeap();
    get_lbl_804D8014()->becomeCurrentHeap();
    fn_800061B8(0x1A);
}

// https://decomp.me/scratch/fkjrQ
void* fn_80006080(u32 size, int alignment) {
    void* data = JKRGetCurrentHeap()->alloc(size, alignment);
    JKRGetCurrentHeap()->getTotalFreeSize();
    JKRGetCurrentHeap()->getFreeSize();

    JKRHeap* curHeap = JKRGetCurrentHeap();

    JKRHeap::sCurrentHeap->getTotalFreeSize();
    curHeap->getFreeSize();
    return data;
}

void fn_80006138(void* ptr) {
    JKRHeap::free(ptr, nullptr);
}

void fn_8000615C(u8 groupID) {
    for (s32 i = 1; i <= groupID; i++) {
        lbl_804D8018->getUsedSize(i);
        lbl_804D8018->freeGroup(i);
    }
}

void fn_800061B8(u8 param_1) {
    sCurHeapGroupId = param_1;

    get_lbl_804D8014()->changeGroupID(param_1);
    lbl_804D8018->changeGroupID(param_1);
}

u8 getCurHeapGroupId() {
    return sCurHeapGroupId;
}

void fn_80006204() {
    lbl_804D8018->becomeCurrentHeap();
}

s32 fn_80006228() {
    return lbl_804D8018->getFreeSize();
}
