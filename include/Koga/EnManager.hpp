#ifndef EN_MANAGER_H_
#define EN_MANAGER_H_

#include <types.h>
#include <JSystem/JGeometry/JGVec3.hpp>
#include <JSystem/JORReflexible.hpp>

#include "Koga/Message.hpp"
#include "Koga/ToolData.hpp"


class EnemyStrategy;
class unkEnCharacter;
class JKRArchive;

namespace Koga {
    class ToolData;
    class EnManager;
    class EnTypesManager;
    class CharacterEvent;
}

const f32 MAX_FLOAT = 3.4028235E+38;

// Fabricated name, subject to change or changed to a class instead
class AppearPointSlot {
public:
    void init(JGeometry::TVec3f*, Koga::ToolData*, int);
    void fn_800E616C(JGeometry::TVec3f*);

    /* 0x0 */ s32 _0;
    /* 0x4 - 0xB */ ToolDataRef mCharacter;
    /* 0xC - 0x13 */ JGeometry::TVec3f mPosition;
    /* 0x18 */ u32 _18;
};

enum CharacterState {
    /* 0 */ DEFAULT_CHARSTATE,
    /* 1 */ ACTIVE_CHARSTATE,
    /* 2 */ INACTIVE_CHARSTATE
};

class unkEnManager1 {
public:
    unkEnManager1();
    ~unkEnManager1();

    void fn_800E9A0C(void*);
    BOOL fn_800E9A58(u32); //param_1 is un-used?
    void fn_800E9ACC();
    void fn_800E9B44();
    void fn_800E9B74();
    BOOL fn_800E9C38(Koga::CharacterEvent*);
    void* fn_800E9C5C();
    BOOL fn_800E9C78();
    void fn_800E9CDC();

    inline bool matchesStatus(s32 state, s32 param_2) {
        return state == mState && param_2 == _8;
    }

    /* 0x0 */ unkEnCharacter* _0; // Probably just Character.hpp/cpp maybe?
    /* 0x4 */ CharacterState mState;
    /* 0x8 */ u32 _8;
    /* 0xC */ u8 _C;
    /* 0xD - 0xF */ u8 padding; 
};

class unkEnManager2 {
public:
    unkEnManager2();
    unkEnManager2(const ToolDataRef&);

    u32 fn_800E601C(); 
    const char* getCreateName();
    ToolDataRef fn_800E6134() const;

    /* 0x0 - 0x7 */ ToolDataRef mCharacter;
    s32 _8; //mTypeIndex?
};

class unkEnManager3 : public Koga::Array<unkEnManager2, 0x80> {
public:
    unkEnManager3();
    ~unkEnManager3();

    void add(unkEnManager2*);
    unkEnManager2* remove(unkEnManager2*);
};

// Fabricated name. Probably just Character.hpp/cpp?
// Not sure if this is a true class, but just made sense based on the data being moved around/accessed
class unkEnCharacter {
public:
    // Currently all untouched until some further decompilation. I believe the args/returns _should_ be correct.
    void fn_800E634C(u16, f32, f32, f32);
    BOOL fn_800E655C(u16, f32, f32);
    BOOL fn_800E66FC(f32, f32, f32);
    f32 fn_800E6C5C();
    void fn_800E6D24(s32, JGeometry::TVec3f*);
    void fn_800E6DE4();
    BOOL fn_800E6ED0();
    void fn_800E6FCC();
    f32 fn_800E7114(void*);
    void fn_800E730C(void*);
    s32 fn_800E7378(void*);
    void fn_800E83A0();
    s32 fn_800E8438(); // Gets the item_table index, which is used to spawn items after character is defeated

    /* 0x000 - 0x7FF unknown, probably some inheritance, like MoveObj? */
    /* 0x000 */ u8 _0[0x800];
    /* 0x800 */ EnemyStrategy* pEnStrategy; // EnManager::vt_14
    /* 0x804 */ void* _804; // unkEnManager1::~unkEnManager1
    /* 0x808 */ void* _808;
    /* 0x80C */ Koga::EnManager* pEnManager;
    /* 0x810 */ u8 pad_810[0x900 - 0x810];
    /* 0x900 */ void* pUnk900;
};

namespace Koga {

    class EnManager : public JORReflexible, public MessageReceiver {
    public:
        EnManager(); // This is wrong because TVec3f gives a constructor that shouldn't be there. Maybe 3 f32's instead.
        /* 0x08 */ virtual ~EnManager();

        void loadCharacterInfo(JKRArchive*);
        void fn_800E46C0(); // Needs more functions decompiled

        // Gets called by JmpMessageSender, also seems to create CharacterEvents to active slots?
        void fn_800E4800(char*); // Could also be some buffer/array
        static BOOL fn_800E4A04(u32);

        /* 0x0C */ virtual BOOL vt_0C(ToolDataRef*); // Something with ItemInfo/OpenDoorNo, could be spawning an enemy?
        /* 0x10 */ virtual BOOL vt_10(ToolDataRef*); // My guess is the opposite, despawning?
        /* 0x14 */ virtual BOOL vt_14(ToolDataRef*, char*); // Something with Luigi name and setting enemy strategy state?

        void fn_800E52BC(ToolData*);
        u32 findLuigiAppearIndex(ToolData*, u32);
        ToolDataRef fn_800E5488(s32);
        
        JGeometry::TVec3f* fn_800E5564(s32);
        u32 fn_800E55AC(s32);
        s32 fn_800E55F0(s32); // Gets _0 member from AppearSlot
        void* fn_800E5600(s32); // Dynamicaly casts Player to MoveObj 
        void* fn_800E5634(s32); // Helper function to get a player object from fn_80069130 (by taking in _E08[param_1]._0?)

        s32 fn_800E5660(JGeometry::TVec3f*, JGeometry::TVec3f*, f32);
        s32 fn_800E56E4(JGeometry::TVec3f*, JGeometry::TVec3f*);
        s32 fn_800E5784(JGeometry::TVec3f*, JGeometry::TVec3f*);

        s32 fn_800E5868(s32, s32);
        unkEnManager1* fn_800E58D4(u32, ToolData*, s32); // Needs more decompilation
        void fn_800E59D4(s32);
        void* fn_800E5A00();
        unkEnCharacter* fn_800E5A14(void*);
        unkEnCharacter* fn_800E5A80(s32); // Requires some lbl to be decompiled: lbl_803D7004
        void fn_800E5ABC(s32);
        void fn_800E5AE8(); // Requires some lbl to be decompiled: lbl_80363BF8
        BOOL fn_800E5B88(); // Requires that fn_800AD39C and its resulting struct/class be decompiled more.
        s32 fn_800E5BF8(u32); // I think this depends on MoveObj, which probably need more details from here.
        s32 fn_800E5D18(const char*); // Requires some lbl to be decompiled: lbl_80363B88
        static int fn_800E5E60(int);  // Requires some lbl to be decompiled: lbl_80363B50
        void fn_800E5E78(const char*);

        static JGeometry::TVec3f* fn_800E9568(s32);
        static s32 fn_800E9594(s32);
        static BOOL fn_800E95C0(s32, JGeometry::TVec3f*, u16*);
        static s32 fn_800E96B8(JGeometry::TVec3f*, JGeometry::TVec3f*, f32);
        static s32 fn_800E96E8(JGeometry::TVec3f*, JGeometry::TVec3f*);
        static s32 fn_800E971C(JGeometry::TVec3f*, JGeometry::TVec3f*);
        static void* fn_800E9750(s32); // Probably returns MoveObj or something similar?
        static s32 fn_800E977C(s32, s32);
        static void fn_800E97B0(s32);
        static void* fn_800E97DC(char*); // Gets something from ToolData by CodeName
        static void* fn_800E98E0(); // Not sure what this returns. Maybe some struct?
        static BOOL fn_800E9914(const char*, int);
        static s32 fn_800E9948(const char*);
        static s32 fn_800E9974(const char*);

        inline s32 getAppearSlotIndex() { return sAppearPointSlotIndex; }
        inline s32 getMaxAppearSlotIndex() { return sAppearPointSlotIndex + 1; }

    public:
        /* 0x04 - 0x803 */  unkEnManager1 _4[0x80];
        /* 0x804 - 0xE07 */ unkEnManager3 _804;
        /* 0xE08 - 0xE3F */ AppearPointSlot _E08[2];
        /* 0xE40 */ Koga::ToolData* mInfoTable;
        /* 0xE44 */ u8 _E44;

        static s32 sAppearPointSlotIndex;
    };
};

// Maybe apart of AppearPointSlot? Looks like compiler generated but unsure
void fn_800E61C0();

// Some TVec3f Helpers? Not sure about args/returns, but would make sense the template class would copy over some of the functions to a class where used.
void fn_800E63AC(JGeometry::TVec3f*, unkEnCharacter*, u16, f32, f32, f32);
BOOL fn_800E65C8(JGeometry::TVec3f*, unkEnCharacter*, u16, f32, f32);
BOOL fn_800E6648(JGeometry::TVec3f*, unkEnCharacter*, JGeometry::TVec3f*, f32, f32, f32);
BOOL fn_800E6764(JGeometry::TVec3f*, unkEnCharacter*, f32, f32, f32);
s32 fn_800E689C(JGeometry::TVec3f*, Koga::ToolData*, s32); // Could be ToolDataRef?
void fn_800E6948(JGeometry::TVec3f*, Koga::ToolData*);
void fn_800E6A3C(JGeometry::TVec3f*, Koga::ToolData*, s32); // Could be ToolDataRef?
void fn_800E6AB8(JGeometry::TVec3f*, Koga::ToolData*, f32);

// All of these are miscelaneous functions I havent touched/reviewed. Feel free to move, re-organize, etc.
bool fn_800E7054();
s32 fn_800E70BC();
bool fn_800E7174(JGeometry::TVec3f*);
bool fn_800E71D4(JGeometry::TVec3f*, s32);
bool fn_800E7280(s32);
void* fn_800E7510(void*, void*);
void fn_800E75B8(JGeometry::TVec3f*, void*);
void fn_800E760C(void*);
void fn_800E7628(void*);
BOOL fn_800E7634(Koga::ToolData*);
bool fn_800E7650(void*);
bool fn_800E7698(s32, void**, void**);
void fn_800E7ED8(void*, void*);

// Could be another sub-class? Unsure
void* fn_800E7FC0(void*);
void* fn_800E7FF8(void*, s16);
void fn_800E805C(void*, void*);
void fn_800E8098(void*);

// All of these are miscelaneous functions I havent touched/reviewed in depth. Feel free to move, re-organize, etc.
void fn_800E8180();
s32 fn_800E82AC(f32);
void fn_800E82D8(void*, u8);
void fn_800E83A0(void*);
void fn_800E8438(void*);
s32 fn_800E85C8(s32);
void fn_800E87B0(u8*, s32); //maybe static, has to deal with itemappeartable
void fn_800E8880(void*);
s32 fn_800E8904(void*, JGeometry::TVec3f*, void*);
void fn_800E8C40(JGeometry::TVec3f*, void*);
s32 fn_800E8EF4(void*, JGeometry::TVec3f*, void*);
void fn_800E9174(JGeometry::TVec3f*, f32, f32, f32);
void fn_800E9184(JGeometry::TVec3f*, JGeometry::TVec3f*);
void* fn_800E9548();

#endif
