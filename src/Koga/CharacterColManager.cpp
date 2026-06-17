#include "Koga/CharacterColManager.hpp"
#include <types.h>
#include "Unsorted/ActorDataList.hpp"

static const unkCharactColStruct lbl_8020C7B8 = {};

CharacterColElement::CharacterColElement() : mGlobalActorField0(0), _18(0) {
    _1C.init(&lbl_8020C7B8);
    _4 = &_1C;
    _0 = _1C._9C;
    _8 = 1;
    _C = &_1C._A4;
    _10 = &_1C._B8;
    _1C._A4 = lbl_8020C7B8._14;
    _1C._B8 = lbl_8020C7B8._28;
}

void CharacterColElement::init(int actorIndex) {
    u32 someOffset;

    _1C._9C = 0;
    mGlobalActorField0 = getActorField0ByIndex(actorIndex);
    ActorData* actData = &lbl_8038E118[actorIndex];
    if (actData != nullptr) {
        someOffset = getActorField0ByIndex(actorIndex);
        actData = &lbl_8038DD00[someOffset];
    }

    someOffset = 0;
    _18 = 0;
    for (int index = 0; index < actData->_0; index++) {
        _1C.init(reinterpret_cast<const unkCharactColStruct*>(actData->_4 + someOffset));
        someOffset += 20;
    }

    _4 = &_1C;
    _0 = _1C._9C;
    _8 = actData->_8;
    _C = &_1C._A4;
    _10 = &_1C._B8;

    unkActorData1* someSrcData = actData->_C;
    if (someSrcData != nullptr) {
        _1C._A4 = *someSrcData;
    }

    unkActorData1* otherSrcData = actData->_10;
    if (someSrcData != nullptr) {
        _1C._B8 = *otherSrcData;
    }
    return;
}

CharacterColManager::CharacterColManager() {
    mCharColElements = new CharacterColElement[381];

    for (u32 i = 0; i < sizeof(CharacterColElement); i++) {
        CharacterColElement* charElm = &mCharColElements[i];
        charElm->init(i);
    }
}

CharacterColElement::~CharacterColElement() {}

CharacterColManager::~CharacterColManager() {
    delete [] mCharColElements;
}


unkCharacterElementClass::unkCharacterElementClass() {
    _A4._0 = nullptr;
}

unkCharacterElementClass::~unkCharacterElementClass() {}

void unkCharacterElementClass::init(const unkCharactColStruct* param_1) {
    _A4._0 += 1;
    _0[_A4._0] = _A4;
}
