#include "Koga/EnManager.hpp"
#include "Koga/EnTypesManager.hpp"
#include "Koga/GameModeUtil.hpp"
#include "Koga/ToolData.hpp"
#include "Koga/MissionMode.hpp"
#include "Unsorted/800627D8.hpp"
#include "Unsorted/AssortedEnManager.hpp"
#include "types.h"

#include <JSystem/JKernel/JKRArchive.hpp>
#include <dolphin/mtx.h>
#include <string.h>


namespace Koga {

    // https://decomp.me/scratch/fWEep
    EnManager::EnManager() : mInfoTable(nullptr) {
        _E44 = 0;
        _804.mArraySize = 0;
        mInfoTable = new ToolData();
    }

    // https://decomp.me/scratch/FXGcc
    EnManager::~EnManager() {
        delete mInfoTable;
    }

    void EnManager::loadCharacterInfo(JKRArchive* pArc) {
        mInfoTable->attach(reinterpret_cast<ToolData::JMapData*>(
            pArc->getResource('JMP ', "CharacterInfo")));
        EnManager::fn_800E52BC(mInfoTable);
    }

    // https://decomp.me/scratch/maIlk
    void EnManager::fn_800E46C0() {
        _E44 = 1;
        s32 maxPoint = getMaxAppearSlotIndex();

        for (int i = 0; i < maxPoint; i++) {
            _E08[i].fn_800E616C(&_E08[i].mPosition);
        }
        fn_80068EF8();

        unkEnManager1* currElm = &_4[0];
        for (int j = 0; j < maxPoint; currElm++, j++) {
            AppearPointSlot* appearPoint = &_E08[j];
            unkEnCharacter* temp4 = fn_800E5A14(nullptr);
            currElm->fn_800E9A0C(temp4);
            void* someObj = currElm->fn_800E9C5C();
            //appearPoint->_0 = someObj->_38; // also gets _38 from this?;
            fn_800BF8B8(currElm->_0, appearPoint->mCharacter.getToolData(), appearPoint->mCharacter.getEntryIndex());
            currElm->fn_800E9CDC();
        }

        u32 i2;
        void* temp4;
        unkEnManager1* currElm2;
        unkEnManager1* startElm;

        startElm = _4 + maxPoint;
        for (i2 = 0; i2 < 4; i2++) {
            temp4 = fn_800DB06C(i2);
            currElm2 = startElm;
            for (int k = 0; k < fn_800E5E60(i2); k++, currElm2++, startElm++) {
                void* temp5 = fn_800E5A14(temp4);
                currElm2->fn_800E9A0C(temp5);
                currElm2->fn_800E9ACC();
            }
        }
    }

    void EnManager::fn_800E52BC(ToolData* pCharacterInfo) {
        s32 appearPoint = sAppearPointSlotIndex + 1;
        u32 currAppearPoint = getLuigiAppearPoint();

        for (s32 i = 0; i < appearPoint; i++) {
            s32 entryIndex = findLuigiAppearIndex(pCharacterInfo, currAppearPoint);

            JGeometry::TVec3f zeroPos, pos;
            if (pCharacterInfo->getDataEntryNum() <= entryIndex) {
                JGeometry::TVec3f zeroPos;
                zeroPos.setAll(0.0f);
                _E08[i].init(&zeroPos, nullptr, -1);
            } else {
                pCharacterInfo->getValue(entryIndex, "pos_x", &pos.x);
                pCharacterInfo->getValue(entryIndex, "pos_y", &pos.y);
                pCharacterInfo->getValue(entryIndex, "pos_z", &pos.z);

                _E08[i].init(&pos, pCharacterInfo, entryIndex);
            }
        }
    }

    u32 EnManager::findLuigiAppearIndex(ToolData* pCharacterInfo, u32 expectedPoint) {
        u32 out;
        s32 luigiAppearPoint = 0;

        while (true) {
            int fieldIndex = pCharacterInfo->searchItemInfo("name");
            luigiAppearPoint = pCharacterInfo->findEntryByValue(fieldIndex, "luigi", luigiAppearPoint);
            if (luigiAppearPoint == -1) {
                return pCharacterInfo->getDataEntryNum();
            }

            out = 0;
            pCharacterInfo->getValue(luigiAppearPoint, "appear_point", &out);
            if (out == expectedPoint) { 
                return luigiAppearPoint;
            }
            
            luigiAppearPoint++;
        }
    }

    // https://decomp.me/scratch/9kvCn
    ToolDataRef EnManager::fn_800E5488(s32 expectedIndex) {
        ToolDataRef out;
        ToolData* pChar = mInfoTable;
        s32 idx = 0;

        while (true) {
            int fieldIndex = pChar->searchItemInfo("name");
            idx = pChar->findEntryByValue(fieldIndex, "luige", idx);
            if (idx == -1) {
                idx = pChar->getDataEntryNum();
                break;
            }

            u32 appearPoint = 0;
            pChar->getValue(idx, "appear_point", &appearPoint);
            if (appearPoint != expectedIndex) {
                break;
            } else {
                idx++;
            }
        }

        ToolData* pCharFinal = mInfoTable;
        if (pCharFinal->getDataEntryNum() <= idx) {
            out.setToolData(nullptr);
            out.setEntryIndex(-1);
        } else {
            out.setToolData(pCharFinal);
            out.setEntryIndex(idx);
        }

        return out;
    }

    // https://decomp.me/scratch/Ztuvi
    JGeometry::TVec3f* EnManager::fn_800E5564(s32 param_1) {
        FORCE_DONT_INLINE;
        if (_E44 != 0) {
            // This probably pulls 0x0 from whatever object this is
            void* someObj = fn_800AD39C(param_1);
            //return someObj->_0; // At least, thats what it looks like?
        }

        return &_E08[param_1].mPosition;
    }

    // https://decomp.me/scratch/cBw99
    u32 Koga::EnManager::fn_800E55AC(s32 param_1) {
        FORCE_DONT_INLINE;
        if (_E44 != 0) {
            void* someObj = fn_800AD39C(param_1);
            //return someObj->_24; // This probably pulls 0x24 from whatever object this is
        }

        return _E08[param_1]._18;
    }

    s32 EnManager::fn_800E55F0(s32 appearSlotIndex) {
        return _E08[appearSlotIndex]._0;
    }

    // Based on ObjDiff, this seems to do some copy constructor stuff but the TVec3f struct seems to give me a lot of issues in this class
    // Also no-inline temproarily because it spills into the other function.
    s32 EnManager::fn_800E5660(JGeometry::TVec3f* pParam_1, JGeometry::TVec3f* out, f32 param_2) {
        FORCE_DONT_INLINE;
        JGeometry::TVec3f localOut;
        s32 result = fn_800E5784(pParam_1, &localOut);

        if (out != nullptr) {
            *out = localOut;
        }

        if (VECMag(localOut) < param_2) {
            return result;
        }

        return -1;
    }

    // https://decomp.me/scratch/AfFrv
    s32 EnManager::fn_800E5784(JGeometry::TVec3f* pParam_1, JGeometry::TVec3f* out) {
        int returnVal = -1;
        int maxAppear = getMaxAppearSlotIndex();
        f32 lowVal = MAX_FLOAT;

        if (maxAppear == 1 && out == nullptr) {
            return 0;
        }
        
        for (int i = 0; i < maxAppear; i++) {
            JGeometry::TVec3f* tVar;
            if (_E44 != 0) {
            // This probably pulls 0x0 from whatever object this is
            void* someObj = fn_800AD39C(i);
            //tVar = someObj->_0; // At least thats what it looks like
            } else {
                AppearPointSlot* tempVar = &_E08[i];
                tVar = &tempVar->mPosition;
            }

            JGeometry::TVec3f localOut;
            PSVECSubtract(tVar, pParam_1, &localOut);
            f32 localMag = VECMag(localOut);

            if (localMag < lowVal) {
                if (out != nullptr) {
                    *out = localOut;
                }
                lowVal = localMag;
                returnVal = i;
            }
        }

        return returnVal;
    }

    // https://decomp.me/scratch/shICK
    s32 EnManager::fn_800E5868(s32 param_1, s32 param_2) {
        FORCE_DONT_INLINE;
        unkEnManager1* temp = fn_800E58D4(param_1, nullptr, -1);
        if (temp == nullptr) return -1;

        if (param_2 >= 0) {
            fn_800C19CC(temp->_0, param_2);
        }

        void* tempObj = temp->fn_800E9C5C();
        //return tempObj->_38;
    }

    // https://decomp.me/scratch/cYSVu
    void EnManager::fn_800E59D4(s32 idx) {
        unkEnManager1* temp = _4;
        temp[idx].fn_800E9ACC();
    }

    // https://decomp.me/scratch/fm1ig
    void EnManager::fn_800E5ABC(s32 param_1) {
        unkEnManager1* temp = _4;
        temp[param_1].fn_800E9B44();
    }

    // https://decomp.me/scratch/3EURE
    void EnManager::fn_800E5E78(const char* pCreateName) {
        unkEnManager2* it = _804.mArr;
        unkEnManager1* end = &_4[0x80];

        while (it != &_804.mArr[_804.mArraySize]) {
            if (strcmp(it->getCreateName(), pCreateName) != 0) {
                it++;
                continue;
            }

            // Some sort of missing struct missing here?
            s32 itEight = it->_8;
            s32 entryIndex = it->mCharacter.getEntryIndex();
            ToolData* charInfo = it->mCharacter.getToolData();
            s32 someVal = fn_800DAC84(itEight);
            unkEnManager1* p = &_4[0];

            while (p != end && !p->matchesStatus(ACTIVE_CHARSTATE, someVal)) {
                p++;
            }

            unkEnManager1* found;
            if (p != end) {
                fn_800BF8B8(p->_0, charInfo, entryIndex);
                if (!p->fn_800E9A58(itEight)) {
                    p->fn_800E9ACC();
                    found = nullptr;
                } else {
                    found = p;
                }
            } else {
                found = nullptr;
            }

            if (found != nullptr) {
                it = _804.remove(it);
            }
        }
    }
}

unkEnManager2::unkEnManager2() {
    _8 = -1;
}

// https://decomp.me/scratch/IqD70
unkEnManager2::unkEnManager2(const ToolDataRef& rDest) {
    mCharacter = rDest;
    _8 = fn_800DABA4(mCharacter);
}

// https://decomp.me/scratch/6sXfk
u32 unkEnManager2::fn_800E601C() {
    JGeometry::TVec3f pos;

    mCharacter.getToolData()->getValue(mCharacter.getEntryIndex(), "pos_x", &pos.x);
    mCharacter.getToolData()->getValue(mCharacter.getEntryIndex(), "pos_y", &pos.y);
    mCharacter.getToolData()->getValue(mCharacter.getEntryIndex(), "pos_z", &pos.z);

    return fn_80017ADC(pos, -1);
}

// https://decomp.me/scratch/cfVnh
const char* unkEnManager2::getCreateName() {
    const ToolDataRef vRef = fn_800E6134();
    const char* create_name;
    
    if (vRef.isValid()) {
        mCharacter.getToolData()->getValue(mCharacter.getEntryIndex(), "create_name", &create_name);
    }

    return create_name;
}

// https://decomp.me/scratch/bq3Q2
ToolDataRef unkEnManager2::fn_800E6134() const {
    return mCharacter;
}

void AppearPointSlot::init(JGeometry::TVec3f* pPos, Koga::ToolData* pCharInfo, int entryIndex) {
    mCharacter.setToolData(pCharInfo);
    mCharacter.setEntryIndex(entryIndex);
    mPosition = *pPos;
}

void AppearPointSlot::fn_800E616C(JGeometry::TVec3f* pParam_1) {
    _18 = fn_80017ADC(*pParam_1, -1);
}

unkEnManager1::unkEnManager1() {
    _0 = 0;
    mState = DEFAULT_CHARSTATE;
    _8 = 0;
}

unkEnManager3::unkEnManager3() {}

unkEnManager3::~unkEnManager3() {}

// https://decomp.me/scratch/vwGnl
void unkEnManager3::add(unkEnManager2* param_1) {
    add(param_1);
}

unkEnManager2* unkEnManager3::remove(unkEnManager2* pStartElm) {
    return eraseMember(pStartElm);
}

// Does not match due to some ToolData inline shenanigans. Seems to match more as a u32 input though than u8
// https://decomp.me/scratch/PdZKG
ToolDataRef ToolDataRef::fn_800E82D8(u32 param_1) {
    ToolDataRef vRef;
    if (param_1 == -1) {
        vRef.setEntryIndex(-1);
        return vRef;
    }

    Koga::ToolData* treasureTable = Koga::GameModeUtil::getJmpResource("treasuretable");
    if (treasureTable == nullptr) {
        vRef.setEntryIndex(-1);
        return vRef;
    }

    int roomNo = treasureTable->findEntryByValue(treasureTable->searchItemInfo("room"), param_1 & 0xFF, 0);
    if (roomNo == -1) {
        vRef.setEntryIndex(-1);
        return vRef;
    }

    vRef.setToolData(treasureTable);
    vRef.setEntryIndex(roomNo);
    return vRef;
}


// Does not match due to some ToolData inline shenanigans
// https://decomp.me/scratch/iXsZ8
ToolDataRef ToolDataRef::fn_800E84CC(s32 param_1) {
    ToolDataRef vRef;
    Koga::ToolData* itemAppear = Koga::GameModeUtil::getJmpResource("itemappeartable");
    
    if (itemAppear == nullptr) {
        vRef.setToolData(nullptr);
        vRef.setEntryIndex(-1);
        return ToolDataRef(&vRef);
    }

    int entryIdx = fn_800E85C8(param_1);
    if (entryIdx > itemAppear->getDataEntryNum()) {
        vRef.setToolData(nullptr);
        vRef.setEntryIndex(-1);
        return ToolDataRef(&vRef);
    }

    // Calls upon fn_80009638() to get some value, which is probably the below fieldIdx
    int fieldIdx = 0;
    vRef.findInfoTableName(itemAppear->getStringValue(entryIdx, fieldIdx));
    return vRef;
}

// https://decomp.me/scratch/mcYqn
ToolDataRef ToolDataRef::fn_800E8658(s32 param_1, s32 param_2, s32 param_3) {
    ToolDataRef tmp;
    Koga::ToolData* itemFishing = Koga::GameModeUtil::getJmpResource("itemfishingtable");

    if (itemFishing == nullptr) {
        tmp.setToolData(nullptr);
        tmp.setEntryIndex(-1);
        return ToolDataRef(&tmp);
    }

    if (param_1 <= itemFishing->getDataEntryNum()) {
        tmp.setToolData(nullptr);
        tmp.setEntryIndex(-1);
        return ToolDataRef(&tmp);
    }

    int fieldCount = itemFishing->getJMapData()->mNumFields;
    if (fieldCount < param_3) {
        if (fieldCount <= param_2) {
            param_3 = fieldCount - 1;
        }
    } 
    
    else if (param_3 <= param_2) {
        param_2 = (param_2 - param_3) - (
            ((param_2 - param_3) / (fieldCount - param_3) * (fieldCount - param_3))) + param_3;
    }

    const char* itemName = itemFishing->getStringValue(param_2, param_3);
    if (strcmp(itemName, "-") == 0) {
        tmp.setToolData(nullptr);
        tmp.setEntryIndex(-1);
        return ToolDataRef(&tmp); 
    }

    return ToolDataRef::findInfoTableName(itemName);;
}

ToolDataRef::ToolDataRef(const ToolDataRef* pSrc) {
    setToolData(pSrc->mToolData);
    setEntryIndex(pSrc->mEntryIndex);
}

// https://decomp.me/scratch/qYZ9J
ToolDataRef ToolDataRef::findInfoTableName(const char* pName) {
    ToolDataRef temp;
    Koga::ToolData* itemInfo = Koga::GameModeUtil::getJmpResource("iteminfotable");
    int fieldIndex = itemInfo->searchItemInfo("name");
    int charFound = itemInfo->findEntryByValue(fieldIndex, pName, 0);

    if (charFound == -1) {
        temp.setToolData(nullptr);
        temp.setEntryIndex(-1);
    } else {
        temp.setToolData(itemInfo);
        temp.setEntryIndex(charFound);
    }

    return temp;
}

// Needed to match isNameValid/Money for now, otherwise it inlines this function.
// https://decomp.me/scratch/JdML7
const char* ToolDataRef::getName() {
    FORCE_DONT_INLINE;
    const char* name;

    if (isValid()) {
        getToolData()->getValue(mEntryIndex, "name", &name);
    }
    return name;
}

// Matches except one instruction. Also depends on the getName above to not inline.
// https://decomp.me/scratch/wZ68w
const BOOL ToolDataRef::isNameValid() {
    BOOL nameValid = true;

    if (isValid()) {
        if (strcmp(getName(), "nothing") != 0) {
            nameValid = false;
        }
    }

    return nameValid;
}

// Matches except one instruction. Also depends on the getName above to not inline.
// https://decomp.me/scratch/WT1gF
const BOOL ToolDataRef::isNameMoney() {
    BOOL nameValid = true;

    if (isValid()) {
        if (strcmp(getName(), "money") != 0) {
            nameValid = false;
        }
    }

    return nameValid;
}
 
namespace Koga {

    // Matches but underlying function gets inlined, causing no match currently.
    JGeometry::TVec3f* EnManager::fn_800E9568(s32 appearSlotIndex) {
        return Koga::MissionMode::getMissionMode()->getEnManager()->fn_800E5564(appearSlotIndex);
    }

    // Matches but underlying function gets inlined, causing no match currently.
    s32 EnManager::fn_800E9594(s32 appearSlotIndex) {
        return Koga::MissionMode::getMissionMode()->getEnManager()->fn_800E55AC(appearSlotIndex);
    }

    // https://decomp.me/scratch/Zhrs6
    BOOL EnManager::fn_800E95C0(s32 expectedPoint, JGeometry::TVec3f* pParam_1, u16* out) {
        ToolDataRef appearEntry = Koga::MissionMode::getMissionMode()->getEnManager()->fn_800E5488(expectedPoint);
        ToolData* pCharInfo = appearEntry.getToolData();
        s32 entryIndex = appearEntry.getEntryIndex();
        bool bPointFound = false;

        if (pCharInfo != nullptr && 0 <= entryIndex) { //if (appearEntry.isValid()) { 
            bPointFound = true;
        }

        if (!bPointFound) {
            return false;
        }
        
        pCharInfo->getValue(entryIndex, "pos_x", &pParam_1->x);
        pCharInfo->getValue(entryIndex, "pos_y", &pParam_1->y);
        pCharInfo->getValue(entryIndex, "pos_z", &pParam_1->z);

        if (out != nullptr) {
            u32 dir = 0;
            pCharInfo->getValue(entryIndex, "dir_y", &dir);
            *out = dir;
        }

        return true;
    }

    s32 EnManager::fn_800E96B8(JGeometry::TVec3f* pParam_1, JGeometry::TVec3f* pParam_2, f32 param_3) {
        return Koga::MissionMode::getMissionMode()->getEnManager()->fn_800E5660(pParam_1, pParam_2, param_3);
    }

    s32 EnManager::fn_800E96E8(JGeometry::TVec3f* pParam_1, JGeometry::TVec3f* pParam_2) {
        return Koga::MissionMode::getMissionMode()->getEnManager()->fn_800E56E4(pParam_1, pParam_2);
    }

    s32 EnManager::fn_800E971C(JGeometry::TVec3f* pParam_1, JGeometry::TVec3f* pParam_2) {
        return Koga::MissionMode::getMissionMode()->getEnManager()->fn_800E5784(pParam_1, pParam_2);
    }

    void* EnManager::fn_800E9750(s32 param_1) {
        return Koga::MissionMode::getMissionMode()->getEnManager()->fn_800E5600(param_1);
    }

    s32 EnManager::fn_800E977C(s32 param_1, s32 param_2) {
        return Koga::MissionMode::getMissionMode()->getEnManager()->fn_800E5868(param_1, param_2);
    }

    // https://decomp.me/scratch/fDI0r
    void EnManager::fn_800E97B0(s32 param_1) {
        Koga::MissionMode::getMissionMode()->getEnManager()->fn_800E59D4(param_1);
    }
}

// https://decomp.me/scratch/LLh5c
unkEnManager1::~unkEnManager1() {
    if (_0 != nullptr) {
        // Call some destructor through _0+0x804
    }
}

// https://decomp.me/scratch/EmrGG
void unkEnManager1::fn_800E9A0C(void* pParam_1) {
    //_0 = pParam_1; // It could just be a pointer to an unkEnCharacter object?
    // _8 = fn_800DAC84(pParam_1); // This should be getting the 0x808 offset of param_1, then a secondary 0x3C offset?
    mState = INACTIVE_CHARSTATE;
    _C = 0;
}

// https://decomp.me/scratch/IUVOm
BOOL unkEnManager1::fn_800E9A58(u32) {
    mState = INACTIVE_CHARSTATE;
    _C = 0;
    char temp = fn_800C15E0(_0);
    
    if (temp != 0) {
        fn_800E9CDC();
        // Then calls _0 offset 0x800, then 0xC, maybe some virtual table call?
    }


    return temp != 0;
}

// 99%, some stack mismanagement but could also be related to function inputs here.
void unkEnManager1::fn_800E9ACC() {
    mState = ACTIVE_CHARSTATE;
    fn_800C17EC(_0);
    JGeometry::TVec3f defaultPos = JGeometry::TVec3f(-32000.0f);
    fn_80067CB0(fn_800E9C5C(), defaultPos.x, defaultPos.y, defaultPos.z);
}

void unkEnManager1::fn_800E9B44() {
    if (mState == 2) {
        fn_800BF81C(_0);
    }
}
