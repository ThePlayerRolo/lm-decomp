#include "Koga/CharacterColManager.hpp"
#include "types.h"
#include "Unsorted/ActorDataList.hpp"

static const unkCharactColStruct lbl_8020C7B8 = {
    -1, 
    0x42480000,
    0,
    0x42480000,
    0,
};

CharacterColElement::CharacterColElement() {
    mGlobalActorField0 = _8;
    _18 = 1;
    fn_800BE9E0(&_1C); //Some sort of constructor for 0x1C it seems like
    fn_800BEA2C(_1C, &lbl_8020C7B8);
    _4 = &_1C;
    _0 = _BC;
    _8 = 1;
    _C = &_C0;
    _10 = &_D4;
    _C0 = lbl_8020C7B8._14;
    _D4 = lbl_8020C7B8._28;
}

void CharacterColElement::init(int actorIndex) { 
    u32 someOffset;
    
    _BC = 0;
    mGlobalActorField0 = getActorField0ByIndex(actorIndex);
    ActorData* actData = reinterpret_cast<ActorData*>(&lbl_8038E118 + actorIndex * 4);
    if (actData != nullptr) {
        someOffset = getActorField0ByIndex(actorIndex);
        actData = reinterpret_cast<ActorData*>(&lbl_8038DD00[someOffset]);
    }

    someOffset = 0;
    _18 = 0;
    for (int index = 0; index < actData->_0; index++) {
        fn_800BEA2C(&_1C, reinterpret_cast<const unkCharactColStruct*>(&actData->_4 + someOffset));
        someOffset += 20;
    }

    _4 = &_1C;
    _0 = _BC;
    _8 = actData->_8;
    _C = &_C0;
    _10 = &_D4;

    unkActorData1* someSrcData = actData->_C;
    if (someSrcData != nullptr) {
        _C0 = *someSrcData;
    }

    unkActorData2* otherSrcData = actData->_10;
    if (someSrcData != nullptr) {
        _D4 = *otherSrcData;
    }
    return;
}

CharacterColManager::CharacterColManager() {
    mCharColElements = new CharacterColElement[381];

    for (int i = 0; i < 381; i++) {
        CharacterColElement* charElm = &mCharColElements[i];
        charElm->init(i);
    }
}

CharacterColManager::~CharacterColManager() {
    delete [] mCharColElements;
}
