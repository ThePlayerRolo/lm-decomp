#ifndef ACTORLIST_HPP
#define ACTORLIST_HPP

// Starting at 0x8033B590 is an Actor Object List. The list contains elements up to 24 bytes long, 
// broken down by the ActorData class. Actor Data global list ends at 0x8033DF40

#include "types.h"

struct unkActorData1 { //Might be a class, would need to dig further.
    u32 _0; //Potentially fabricated, but based on lwz instructions
    u32 _4;
    u32 _8;
    u32 _C;
    u32 _10;
};

class ActorData {
    public:
        /* 0x0 */ int _0;
        /* 0x4 */ u32 _4;
        /* 0x8 */ u32 _8;
        /* 0xC */ unkActorData1* _C;
        /* 0x10 */ unkActorData1* _10; // Could be the same as the above.
        /* 0x14 */ u16 _14;
        /* 0x16 */ u16 _16;
        /* 0x18 */ char* mActorName;
};

// This might make more sense in a Util class, unsure at this time without digging more.
char* getActorNameByIndex(int actorIndex); //8006a3a4
u32 getActorField0ByIndex(int actorIndex); //8006a354
u16 getActorField4ByIndex(int actorIndex); //8006a36c

ActorData* lbl_8038E118; //Some Pointer to some ActorData, possibly pointers to what slot the Actor is loaded into?
ActorData* lbl_8038DD00; //Some array pointer to some actor part or something similar?

#endif
