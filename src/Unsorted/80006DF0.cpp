#include "Unsorted/80006DF0.hpp"
#include "Unsorted/80005EB8.hpp"
#include "Unsorted/LMDvdFile.hpp"
#include <dolphin/os/OSFastCast.h>

//TODO: Better name for this
struct LMDvdThread : public OSThread {
    /* 0x310 */ OSMessageQueue _310;
    /* 0x330 */ void* _330[64];
    /* 0x430 */ LMDvdFileInfo* _430;
};

void* sDvdThreadStack[2048];
LMDvdThread sDvdThread1;

static void initDvdThreadInternal(LMDvdThread* thread);

void initDvdThread() {
    initDvdThreadInternal(&sDvdThread1);
}

//Needs to be a member of LMDVDFileInfo for matching
void LMDvdFileInfo::fn_80006E18() {
    OSSendMessage(&sDvdThread1._310, this, OS_MESSAGE_BLOCK);
}

//https://decomp.me/scratch/iEJfp
static void* createThreadCallback(void* pPtr) {
    OSInitFastCast();

    while (true) {
        void* msg;
        OSReceiveMessage(&sDvdThread1._310, msg, OS_MESSAGE_BLOCK);

        LMDvdFileInfo* info = (LMDvdFileInfo*)msg;

        if (info->_64 == nullptr) {
            u8 groupId = fn_800061B8(info->_80);

            info->_64 = (LMDvdFileInfoBlock*)fn_80006258(info->_60, LMDvdFile::getCurUnk4() * 32);

            //Have no idea what was meant to be for since the block of code for it is optimized out sooooooo
            if (info->_64 == nullptr) { info = info; }

            fn_800061B8(groupId);
            info->_84 = 1;
        }

        s32 readResult = DVDReadPrio(info, info->_64, info->_60, 0, 2);
        switch (readResult) {
            case 1:
            case DVD_RESULT_IGNORED:
            case -3:
            case -1:
            LMDvdFile::closeFile(nullptr, info);
            u8 groupId = fn_800061B8(info->_80);
            if (info->_78 != nullptr) {
                info->_78(info->_64, info);
            }

            if (lbl_804D8028 == FALSE) {
                if (info->_74 != nullptr) {
                    info->_74(nullptr, info);
                }

                fn_800061B8(groupId);

                sDvdThread1._430 = sDvdThread1._430->_7C;
            }
            break;
        }
    }
}

//https://decomp.me/scratch/heDFD
static void initDvdThreadInternal(LMDvdThread* thread) {
    OSInitMessageQueue(&thread->_310, thread->_330, ARRAY_COUNT(thread->_330));
    thread->_430 = LMDvdFile::getFileInfoArray();
    OSCreateThread(thread, createThreadCallback, nullptr, sDvdThreadStack, sizeof(sDvdThreadStack), 10, OS_THREAD_ATTR_DETACH);
    OSResumeThread(thread);
}
