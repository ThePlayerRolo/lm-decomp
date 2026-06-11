#ifndef JMP_MESSAGE_H_
#define JMP_MESSAGE_H_

#include "JSystem/JORReflexible.hpp"
#include "Koga/Message.hpp"

namespace Koga {
    class ToolData;
}

class unkJmpMessageSender1 {
public:
    unkJmpMessageSender1();

    /* 0x0 */ s32 _0;
    /* 0x4 */ u8 _4[0xC];
};

class unkJmpMessageSender1Arr {
public:
    unkJmpMessageSender1Arr();
    ~unkJmpMessageSender1Arr();


    /* 0x000 */ unkJmpMessageSender1 _0[200];
    /* 0xC80 */ s32 _C80;
};

class unkJmpMessageSender2 : public Koga::Array<Koga::ToolData*, 10> {
public:
    unkJmpMessageSender2() { }
    ~unkJmpMessageSender2() { }
    void add(Koga::ToolData** member) { Koga::Array<Koga::ToolData*, 10>::add(member); }

    Koga::ToolData* fn_800EBBA8(Koga::ToolData*);
};

class JmpMessageSender : public MessageSender, public JORReflexible {
public:

    JmpMessageSender();

    /* 0x08 */ virtual ~JmpMessageSender();
    /* 0x0C */ virtual void vt_0C();
    /* 0x10 */ virtual void vt_10();

    BOOL fn_800EA900(Koga::ToolData* pData);
    BOOL fn_800EA958(Koga::ToolData* pData);

    void fn_800EB634(Koga::ToolData*, s32, bool);
    BOOL fn_800EAA00(const char*, int);
    void fn_800EAB1C();

    void fn_800EB1DC();
    void fn_800EB27C();
    void fn_800EB528();
    void fn_800EB5CC(u8*);
    void fn_800EB564(u8*);

public:
    /* 0x038 */ unkJmpMessageSender1Arr _38;
    /* 0xCBC */ unkJmpMessageSender2 _CBC;
    /* 0xCE8 */ u8 _CE8;
    /* 0xCE8 */ u8 _CE9[262];
};

#endif
