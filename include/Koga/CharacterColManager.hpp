#ifndef CHARACTER_COLLISION_MANAGER_H_
#define CHARACTER_COLLISION_MANAGER_H_

#include <types.h>
#include <JSystem/JORReflexible.hpp>
#include "Unsorted/ActorDataList.hpp"

struct unkCharactColStruct {
    /* 0x0 */ int _0; // Most Likely an it as the default value is FFFFFFFF anyways
    /* 0x4 */ u32 _4; //Unknown type;
    /* 0x8 */ u32 _8; //Unknown type;
    /* 0xC */ u32 _C; //Unknown type;
    /* 0x10 */ u32 _10; //Unknown type;
    /* 0x14 - 0x28 */ unkActorData1 _14;
    /* 0x28 - 0x3F */ unkActorData1 _28;
};

class unkCharacterElementClass {
public:
    unkCharacterElementClass();
    ~unkCharacterElementClass();
    void init(const unkCharactColStruct*);

    /* 0x0 - 0x78 */ unkActorData1 _0[6];
    /* 0x78 - 0x80 */ u8 _78[8];
    /* 0x80 */ void* _80;
    /* 0x84 - 0x9C */ u8 _84[0x18];
    /* 0x9C */ void* _9C;
    /* 0xA0 */ u32 _A0;
    /* 0xA4 */ unkActorData1 _A4;
    /* 0xB8 */ unkActorData1 _B8;
};

// TODO Maybe a better name here
class CharacterColElement {
    public:
        CharacterColElement();
        void init(int);
        ~CharacterColElement();

    private:
        /* 0x0 */ void* _0; //Another class/struct of some sort.
        /* 0x4 */ unkCharacterElementClass* _4;
        /* 0x8 */ u32 _8;
        /* 0xC */ unkActorData1* _C;
        /* 0x10 */ unkActorData1* _10;
        /* 0x14 */ u32 mGlobalActorField0; //There is some global Actor data/struct that this gets field 0x0 for
        /* 0x18 */ u8 _18;
        /* 0x19-0x1B */ u8 padding[3];
        /* 0x1C */ unkCharacterElementClass _1C;
};

class CharacterColManager : public JORReflexible {
public:
    CharacterColManager();
    /* 0x08 */ virtual ~CharacterColManager();


public:
    /* 0x04 */ CharacterColElement* mCharColElements;
};

#endif
