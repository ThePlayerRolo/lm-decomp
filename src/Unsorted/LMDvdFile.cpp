#include "Unsorted/LMDvdFile.hpp"
#include "Unsorted/80005EB8.hpp"
#include "Unsorted/80006DF0.hpp"
#include <JSystem/JKernel/JKRHeap.hpp>
#include <JSystem/JKernel/JKRMemArchive.hpp>
#include <JSystem/JUtility/JUTGamePad.hpp>

extern JUTGamePad* sGamePad;
extern void fn_800473F8(s16);
extern s32 lbl_804D80AC;

LMDvdFileInfo LMDvdFile::sFileInfoArray[MAX_FILE_INFO_ARR];
LMDvdFile LMDvdFile::sCurDvdFile;
BOOL lbl_804D8028;

void* fn_80006258(u32 size, int align) {
    return fn_80006080(size, align);
}

LMDvdFileInfo* LMDvdFile::getFileInfoArray() {
    return &sFileInfoArray[0];
}

void LMDvdFile::checkDVDStatus() {
    //TODO: Remove this
    u32 padStack;

    s32 driveStatus = DVDGetDriveStatus();

    if (lbl_804D8028 != FALSE) {
        driveStatus = DVD_STATE_FATAL_ERROR;
    }

    switch (driveStatus) {
    case DVD_STATE_FATAL_ERROR:
        sGamePad->stopMotor();
        lbl_804D80AC = 1;
        break;
    case DVD_STATE_END:
        lbl_804D80AC = 0;
        break;
    case DVD_STATE_BUSY:
        if (DVDCheckDisk() != FALSE) {
            lbl_804D80AC = 0;
        } else {
            driveStatus = 3;
            sGamePad->stopMotor();
            lbl_804D80AC = 1;
        }
        break;
    case DVD_STATE_COVER_CLOSED:
        sGamePad->stopMotor();
        lbl_804D80AC = 1;
        break;
    case DVD_STATE_NO_DISK:
        sGamePad->stopMotor();
        lbl_804D80AC = 1;
        break;
    case DVD_STATE_COVER_OPEN:
        sGamePad->stopMotor();
        lbl_804D80AC = 1;
        break;
    case DVD_STATE_WRONG_DISK:
        sGamePad->stopMotor();
        lbl_804D80AC = 1;
        break;
    case DVD_STATE_RETRY:
        sGamePad->stopMotor();
        lbl_804D80AC = 1;
        break;
    }
    fn_800473F8(driveStatus);
}

void LMDvdFile::init() {
    //TODO: Remove this
    FORCE_DONT_INLINE

    LMDvdFileInfo* info = _8->_7C;
    while (true) {
        s32 blockStatus;
        blockStatus = DVDGetCommandBlockStatus(&info->cb);
        if (blockStatus != DVD_COMMAND_READ) break;
    }
    _8 = info;
    _8->_64 = nullptr;
    _8->_68 = nullptr;
    _8->mArchive = nullptr;
    _8->_78 = nullptr;
    _8->_74 = nullptr;
    _8->_80 = getCurHeapGroupId();

    OSReceiveMessage(&_8->_3C, nullptr, OS_MESSAGE_NOBLOCK);
}

bool LMDvdFile::open(const char* pFileName, LMDvdFileInfoBlock* param_2) {
    //TODO: Remove this
    FORCE_DONT_INLINE

    LMDvdFileInfo* info = _8;
    while (true) {
        s32 blockStatus;
        blockStatus = DVDGetCommandBlockStatus(&info->cb);
        if (blockStatus != DVD_COMMAND_READ) break;
    }

    DVDOpen((char*)pFileName, info);

    _8->_60 =  info->length + 0x1F & 0xFFFFFFE0;
    _8->_84 = 0;
    _8->_64 = param_2;

    _8->fn_80006E18();
    return true;
}

//https://decomp.me/scratch/ek40V
void* LMDvdFile::open(const char* pFileName, LMDvdFileInfoCallback param_2, LMDvdFileInfoBlock* param_3, s32 param_4) {
    //TODO: Remove this
    FORCE_DONT_INLINE
    _8->_74 = param_2;
    _8->_70 = param_4;

    LMDvdFileInfo* info = _8;

    while (true) {
        s32 blockStatus;
        blockStatus = DVDGetCommandBlockStatus(&info->cb);
        if (blockStatus != DVD_COMMAND_READ) break;
    }

    DVDOpen((char*)pFileName, info);
    _8->_60 =  info->length + 0x1F & 0xFFFFFFE0;
    _8->_84 = 0;
    _8->_64 = param_3;

    _8->fn_80006E18();
    _0++;

    return _8->_64;
}

void fn_800065A8() {
    initDvdThread();

    LMDvdFileInfo* curIndex = LMDvdFile::getFileInfoArray();

    LMDvdFile::sCurDvdFile._4 = 1;
    LMDvdFile::sCurDvdFile._0 = 0;
    LMDvdFile::sCurDvdFile._8 = LMDvdFile::getFileInfoArray();

    for (s32 i = 0; i < MAX_FILE_INFO_ARR; i++) {
        curIndex->_7C = &LMDvdFile::sFileInfoArray[i + 1];
        OSInitMessageQueue(&curIndex->_3C, &curIndex->_5C, 1);
        curIndex++;
    }

    LMDvdFile::sFileInfoArray[MAX_FILE_INFO_ARR - 1]._7C = LMDvdFile::getFileInfoArray();
}

void* LMDvdFileOpen(const char* pFileName, LMDvdFileInfoBlock* param_2) {
    LMDvdFile::sCurDvdFile.init();
    LMDvdFile::sCurDvdFile._8->_74 = nullptr;
    LMDvdFile::sCurDvdFile._8->_70 = 0;

    if (LMDvdFile::sCurDvdFile.open(pFileName, param_2)) {
        LMDvdFile::sCurDvdFile._0++;
    }

    u32 msg;

    OSReceiveMessage(&LMDvdFile::sCurDvdFile._8->_3C, &msg, OS_MESSAGE_BLOCK);

    return LMDvdFile::sCurDvdFile._8->_64;
}

//https://decomp.me/scratch/YKS45
void* LMDvdFileOpen(const char* pFileName, LMDvdFileInfoCallback cb, LMDvdFileInfoBlock* pBlock, s32 param_4) {
    void* ret;

    // Seems like inlined init, though based on LMDvdFileOpen it could not be?
    LMDvdFileInfo* info = LMDvdFile::sCurDvdFile._8->_7C;
    while (true) {
        s32 blockStatus;
        blockStatus = DVDGetCommandBlockStatus(&info->cb);
        if (blockStatus != DVD_COMMAND_READ) break;
    }
    LMDvdFile::sCurDvdFile._8 = info;
    LMDvdFile::sCurDvdFile._8->_64 = 0;
    LMDvdFile::sCurDvdFile._8->_68 = nullptr;
    LMDvdFile::sCurDvdFile._8->mArchive = nullptr;
    LMDvdFile::sCurDvdFile._8->_78 = nullptr;
    LMDvdFile::sCurDvdFile._8->_74 = nullptr;
    LMDvdFile::sCurDvdFile._8->_80 = getCurHeapGroupId();

    OSReceiveMessage(&LMDvdFile::sCurDvdFile._8->_3C, nullptr, OS_MESSAGE_NOBLOCK);

    LMDvdFile::sCurDvdFile._8->_74 = cb;
    LMDvdFile::sCurDvdFile._8->_70 = param_4;

    if (LMDvdFile::sCurDvdFile.open(pFileName, pBlock)) {
        LMDvdFile::sCurDvdFile._0++;
        ret = LMDvdFile::sCurDvdFile._8->_64;
    }

    return ret;
}

static void fn_80006D28(void* param_1, LMDvdFileInfo* param_2);
static void fn_80006D80(void* param_1, LMDvdFileInfo* param_2);

//https://decomp.me/scratch/KlViD
void* fn_800067D0(const char* pFileName, LMDvdFileInfoCallback param_2, LMDvdFileInfoBlock* param_3, s32 param_4) {
    LMDvdFile::sCurDvdFile._4 = -1;
    // Seems like inlined init, though based on LMDvdFileOpen it could not be?
    LMDvdFileInfo* info = LMDvdFile::sCurDvdFile._8->_7C;

    while (true) {
        s32 blockStatus;
        blockStatus = DVDGetCommandBlockStatus(&info->cb);
        if (blockStatus != DVD_COMMAND_READ) break;
    }
    LMDvdFile::sCurDvdFile._8 = info;
    LMDvdFile::sCurDvdFile._8->_64 = 0;
    LMDvdFile::sCurDvdFile._8->_68 = nullptr;
    LMDvdFile::sCurDvdFile._8->mArchive = nullptr;
    LMDvdFile::sCurDvdFile._8->_78 = nullptr;
    LMDvdFile::sCurDvdFile._8->_74 = nullptr;
    LMDvdFile::sCurDvdFile._8->_80 = getCurHeapGroupId();

    OSReceiveMessage(&LMDvdFile::sCurDvdFile._8->_3C, nullptr, 0);

    if (param_3 != 0) {
        LMDvdFile::sCurDvdFile._8->_84 = 0;
    }
    LMDvdFile::sCurDvdFile._8->_68 = param_3;
    u8 oldGroupId = fn_800061B8(LMDvdFile::sCurDvdFile._8->_80);
    void* ret = fn_80006258(0x68, 4);
    fn_800061B8(oldGroupId);
    LMDvdFile::sCurDvdFile._8->mArchive = (JKRMemArchive*)ret;
    LMDvdFile::sCurDvdFile._8->_78 = fn_80006D80;
    LMDvdFile::sCurDvdFile._8->_74 = param_2;
    LMDvdFile::sCurDvdFile._8->_70 = param_4;

    if (LMDvdFile::sCurDvdFile.open(pFileName, 0)) {
        LMDvdFile::sCurDvdFile._0++;
    }
    LMDvdFile::sCurDvdFile._4 = 1;

    if (param_3 != 0) {
        LMDvdFile::sCurDvdFile._8->_84 = 0;
    }
    return ret;
}

void* fn_80006930(const char* pFileName, LMDvdFileInfoBlock* param_2) {
    void* data = fn_800067D0(pFileName, nullptr, param_2, 0);
    u32 msg;
    OSReceiveMessage(&LMDvdFile::sCurDvdFile._8->_3C, &msg, OS_MESSAGE_BLOCK);
    return data;
}

//https://decomp.me/scratch/WwyKN
JKRMemArchive* LMOpenMemArchive(const char* pFileName, void* param_2) {
    void* buffer;
    JKRMemArchive* archive;
    u32 msg[8];

    LMDvdFile::sCurDvdFile.init();
    LMDvdFile::sCurDvdFile.open(pFileName, 0, (LMDvdFileInfoBlock*)param_2, 0);

    OSReceiveMessage(&LMDvdFile::sCurDvdFile._8->_3C, &msg, OS_MESSAGE_BLOCK);
    buffer = LMDvdFile::sCurDvdFile._8->_64;

    archive = new JKRMemArchive();
    archive->mountFixed(buffer, MBF_1);
    return archive;
}


void* fn_80006A34(const char* pFileName, LMDvdFileInfoCallback param_2, LMDvdFileInfoBlock* param_3, s32 param_4) {
    LMDvdFile::sCurDvdFile._4 = 1;
    // Seems like inlined init, though based on LMDvdFileOpen it could not be?
    LMDvdFileInfo* info = LMDvdFile::sCurDvdFile._8->_7C;

    while (true) {
        s32 blockStatus;
        blockStatus = DVDGetCommandBlockStatus(&info->cb);
        if (blockStatus != DVD_COMMAND_READ) break;
    }
    LMDvdFile::sCurDvdFile._8 = info;
    LMDvdFile::sCurDvdFile._8->_64 = 0;
    LMDvdFile::sCurDvdFile._8->_68 = nullptr;
    LMDvdFile::sCurDvdFile._8->mArchive = nullptr;
    LMDvdFile::sCurDvdFile._8->_78 = nullptr;
    LMDvdFile::sCurDvdFile._8->_74 = nullptr;
    LMDvdFile::sCurDvdFile._8->_80 = getCurHeapGroupId();

    OSReceiveMessage(&LMDvdFile::sCurDvdFile._8->_3C, nullptr, OS_MESSAGE_NOBLOCK);

    LMDvdFile::sCurDvdFile._8->_68 = nullptr;

    u8 oldGroupId = fn_800061B8(LMDvdFile::sCurDvdFile._8->_80);
    void* ret = fn_80006258(0x68, 4);
    fn_800061B8(oldGroupId);

    LMDvdFile::sCurDvdFile._8->mArchive = (JKRMemArchive*)ret;
    LMDvdFile::sCurDvdFile._8->_78 = fn_80006D28;
    LMDvdFile::sCurDvdFile._8->_74 = param_2;
    LMDvdFile::sCurDvdFile._8->_70 = param_4;

    if (LMDvdFile::sCurDvdFile.open(pFileName, param_3)) {
        LMDvdFile::sCurDvdFile._0++;
    }

    return ret;
}

s32 LMDvdFileInfo::getUnk70() {
    return _70;
}

LMDvdFileInfoBlock* LMDvdFileInfo::getUnk64() {
    return _64;
}

u32 LMDvdFileInfo::getLength() {
    return length;
}

JKRMemArchive* LMDvdFileInfo::getArchive() {
    return mArchive;
}

BOOL LMDvdFile::checkCurUnk0() {
    return sCurDvdFile._0 != 0;
}

s32 LMDvdFile::getCurUnk4() {
    return sCurDvdFile._4;
}

void LMDvdFile::checkCurDVDStatus() {
    sCurDvdFile.checkDVDStatus();
}

void LMDvdFile::closeFile(void *pMsg, LMDvdFileInfo* pInfo) {
    sCurDvdFile._0--;
    DVDClose(pInfo);

    //Required to fix regalloc
    void* msg = pMsg;

    switch (DVDGetCommandBlockStatus(&pInfo->cb)) {
        case 0:
            break;
        case 10:
            pInfo->_78 = nullptr;
            pInfo->_74 = nullptr;
            return;
        case -1:
            pInfo->_78 = nullptr;
            pInfo->_74 = nullptr;
            return;
    }
    OSSendMessage(&pInfo->_3C, msg, OS_MESSAGE_NOBLOCK);
}

static void fn_80006C84(void* param_1, LMDvdFileInfo* pInfo) {
    //TODO: Remove this
    FORCE_DONT_INLINE

    s32 size;
    LMDvdFileInfoBlock* header = pInfo->_64;

    if (pInfo->_64->_0 != 'Yay0') {
        lbl_804D8028 = TRUE;
        return;
    }

    size = header->fn_800071C0();

    if (pInfo->_68 == 0) {
        fn_800061B8(pInfo->_80);
        pInfo->_68 = (LMDvdFileInfoBlock*)fn_80006258(size, 0x20);
    }
    LMDvdFileInfoBlock* temp = pInfo->_68;

    header->fn_800071D0(temp);
    JKRFreeToHeap(nullptr, header);
}

//https://decomp.me/scratch/LsFJX
static void fn_80006D28(void* param_1, LMDvdFileInfo* pInfo) {
    if (pInfo->_68->_0 != 'RARC') {
        lbl_804D8028 = TRUE;
    } else {
        if (pInfo->mArchive != nullptr) {
            pInfo->mArchive = &JKRMemArchive(&pInfo->_68, 0, (JKRMemBreakFlag)pInfo->_84);
        }
    }
}

//https://decomp.me/scratch/mjUUS
static void fn_80006D80(void* param_1, LMDvdFileInfo* pInfo) {
    fn_80006C84(param_1, pInfo);

    if (lbl_804D8028 == FALSE) {
        if (pInfo->_68->_0 != 'RARC') {
            lbl_804D8028 = TRUE;
        } else {
            if (pInfo->mArchive != nullptr) {
                pInfo->mArchive = &JKRMemArchive(&pInfo->_68, 0, (JKRMemBreakFlag)pInfo->_84);
            }
        }
    }
}
