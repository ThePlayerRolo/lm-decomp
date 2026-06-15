#ifndef CHARACTER_COLLISION_MANAGER_H_
#define CHARACTER_COLLISION_MANAGER_H_

#include "types.h"
#include "JSystem/JORReflexible.hpp"
#include "Unsorted/ActorDataList.hpp"

struct unkCharactColStruct {
    /* 0x0 */ int _0; // Most Likely an it as the default value is FFFFFFFF anyways
    /* 0x4 */ u32 _4; //Unknown type;
    /* 0x8 */ u32 _8; //Unknown type;
    /* 0xC */ u32 _C; //Unknown type;
    /* 0x10 */ u32 _10; //Unknown type;
    /* 0x14 - 0x27 */ unkActorData1 _14;
    /* 0x28 - 0x3F */ unkActorData2 _28;
};

// TODO Maybe a better name here
class CharacterColElement {
    public:
        CharacterColElement();
        void init(int);
        ~CharacterColElement();

    private:
        /* 0x0 */ u32 _0;
        /* 0x4 */ void* _4;
        /* 0x8 */ u32 _8;
        /* 0xC */ void* _C;
        /* 0x10 */ void* _10;
        /* 0x14 */ u32 mGlobalActorField0; //There is some global Actor data/struct that this gets field 0x0 for
        /* 0x18 */ u8 _18;
        /* 0x19-0x1B */ u8 padding[3];
        /* 0x1C */ void* _1C; // Some struct at least 0xa4 large
        /* 0x20 - 0xA0 */ u8 _20[0x80];
        /* 0xA0 */ void* _A0;
        /* 0xA4 - 0xBC */ u8 _A4[0x18];
        /* 0xBC */ u32 _BC;
        /* 0xC0 */ unkActorData1 _C0;
        /* 0xD4 */ unkActorData2 _D4;
};

class CharacterColManager : public JORReflexible {
public:
    CharacterColManager();
    /* 0x08 */ virtual ~CharacterColManager();


public:
    /* 0x04 */ CharacterColElement* mCharColElements;
};

void fn_800BE9E0(void*); //Some sort of constructor for 0x1C it seems like
void fn_800BE9EC(void*, int); //Some sort of deconstructor for 0x1C it seems like
void fn_800BEA2C(void*, const unkCharactColStruct*); //Some sort of init function for 0x1C it seems

#endif
