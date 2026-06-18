#include "Unsorted/80007018.hpp"
#include <dolphin/os.h>
#include <dolphin/os/OSFastCast.h>

//TODO: Better name for this
struct LMDvdThread2 : public OSThread {
    /* 0x310 */ OSMessageQueue _310;
    /* 0x330 */ s32 _330;
    /* 0x334 */ OSMessageQueue _334;
    /* 0x354 */ s32 _354;
    /* 0x358 */ DvdThread2Callback mCallback;
};

static void* sDvdThread2Stack[4096];
static LMDvdThread2 sDvdThread2;

static void fn_80007144(LMDvdThread2* thread);

void fn_80007018() {
    fn_80007144(&sDvdThread2);
}

void fn_80007040(DvdThread2Callback cb) {
    sDvdThread2.mCallback = cb;
    OSReceiveMessage(&sDvdThread2._334, nullptr, OS_MESSAGE_NOBLOCK);
    OSSendMessage(&sDvdThread2._310, nullptr, OS_MESSAGE_NOBLOCK);
}

void fn_80007090() {
    OSReceiveMessage(&sDvdThread2._334, nullptr, OS_MESSAGE_NOBLOCK);
}

static void* createThreadCallback(void*) {
    OSInitFastCast();

    while (true) {
        OSReceiveMessage(&sDvdThread2._310, nullptr, OS_MESSAGE_BLOCK);

        if (sDvdThread2.mCallback != nullptr) {
            sDvdThread2.mCallback();
        }

        OSSendMessage(&sDvdThread2._334, nullptr, OS_MESSAGE_NOBLOCK);
    }
}

//https://decomp.me/scratch/IRDSH
static void fn_80007144(LMDvdThread2* thread) {
    OSInitMessageQueue(&thread->_310, &thread->_330, 1);
    OSInitMessageQueue(&thread->_334, &thread->_354, 1);
    OSCreateThread(thread, createThreadCallback, nullptr, &sDvdThread2Stack, sizeof(sDvdThread2Stack), 17, OS_THREAD_ATTR_DETACH);
    OSResumeThread(thread);
}
