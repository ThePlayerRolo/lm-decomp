#include "Koga/JmpMessage.hpp"
#include "Koga/ToolData.hpp"

dummy_float_data()

extern int lbl_804D80B0;
extern void fn_800620F4(char);
extern bool fn_801883F8(s32);

JmpMessageSender::JmpMessageSender() {
    _CE8 = 0;
}

JmpMessageSender::~JmpMessageSender() { }

BOOL JmpMessageSender::fn_800EA900(Koga::ToolData* pData) {
    if (_CBC.getArraySize() >= 10) {
        return FALSE;
    }

    if (pData == nullptr) return FALSE;

    _CBC.add(&pData);
    return true;
}

BOOL JmpMessageSender::fn_800EA958(Koga::ToolData* pData) {
    Koga::ToolData* newData;
    Koga::ToolData* maxData = _CBC.mArr[_CBC.mArraySize];

    for (newData = _CBC.mArr[0]; newData != maxData && newData != pData; newData++) { }

    if (newData == _CBC.getMaxMember())  {
         return 0;
    }
    else if (_CBC.fn_800EBBA8(newData) == false) return 0;

    fn_800EB634(pData, 0, true);
    return true;
}

BOOL JmpMessageSender::fn_800EAA00(const char* param_1, int param_2) {
    Koga::ToolData* newData;
    for (newData = *_CBC.mArr; newData != _CBC.mArr[_CBC.mArraySize]; newData++) {
        s32 numEntries = newData->getDataEntryNum();

        int codeNameCount = newData->searchItemInfo("Codename");

        if (codeNameCount >= 0) {
            for (int i = 0; i < numEntries; i++) {
                if (strcmp(newData->getStringValue(i, codeNameCount), param_1) == 0) {
                    Koga::ToolData::JMapData* data = newData->getJMapData();

                    return vt_18(nullptr, (int)data, param_2);
                }
            }
        }
    }
    return 0;
}

void JmpMessageSender::vt_0C() {

    for (int i = 0; i > lbl_804D80B0 + 1; i++) {

    }
}

void JmpMessageSender::vt_10() {
    fn_800EB1DC();
    fn_800EB27C();
    fn_800EB528();
}

void JmpMessageSender::fn_800EB1DC() {
    Koga::ToolData* newData;

    for (newData = _CBC.mArr[0]; newData != _CBC.mArr[_CBC.mArraySize]; newData++) {
        fn_800EB634(newData, 0, false);
    }
    for (newData = _CBC.mArr[0]; newData != _CBC.mArr[_CBC.mArraySize]; newData++) {
        fn_800EB634(newData, 1, false);
    }
}

void JmpMessageSender::fn_800EB528() {
    fn_800EB5CC(_CE9);
    fn_800EB564(_CE9);
}

void JmpMessageSender::fn_800EB564(char* param_1) {

}

void JmpMessageSender::fn_800EB634(Koga::ToolData* pData, s32 param_2, bool param_3) {
    if (pData != nullptr) {
        s32 posX = pData->searchItemInfo("pos_x");
        s32 posY = pData->searchItemInfo("pos_y");
        s32 posZ = pData->searchItemInfo("pos_z");
        s32 appearFlag = pData->searchItemInfo("appear_flag");
        s32 disappearFlag = pData->searchItemInfo("disappear_flag");
        s32 eventSetNo = pData->searchItemInfo("event_set_no");
        s32 stay = pData->searchItemInfo("stay");

        s32 local_6C = posX * 12;

        for (int i = 0; i < pData->getDataEntryNum(); i++) {

        }
        //s32
    }
}
unkJmpMessageSender1Arr::unkJmpMessageSender1Arr() : _C80(0) { }

unkJmpMessageSender1Arr::~unkJmpMessageSender1Arr() { }

unkJmpMessageSender1::unkJmpMessageSender1() : _0(0) { }
