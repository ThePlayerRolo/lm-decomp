#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "Koga/Array.hpp"
#include <types.h>

class MessageReceiver;
typedef bool (MessageReceiver::*MessageCallback1)(int arg0);
typedef bool (MessageReceiver::*MessageCallback2)(int arg0, int arg1);

class MessageRecieverArray : public Koga::Array<MessageReceiver*, 12> {
public:
    MessageRecieverArray() { }
    ~MessageRecieverArray() { }
    void add(MessageReceiver** member) { Koga::Array<MessageReceiver*, 12>::add(member); }
};

class MessageSender {
public:
    MessageSender();

    /* 0x08 */ virtual ~MessageSender();
    /* 0x0C */ virtual void vt_0C() = 0;
    /* 0x10 */ virtual void vt_10() = 0;
    /* 0x14 */ virtual s32 vt_14(MessageCallback1 fn, int arg0);
    /* 0x18 */ virtual s32 vt_18(MessageCallback2 fn, int arg0, int arg1);

    bool addReceiver(void*);

public:
    /* 0x4 */ MessageRecieverArray _4;
};

class IMessageReceiver {
public:
    //Seems to be inlined where its used and doesn't show up in the final binary
    /* 0x08 */ inline virtual ~IMessageReceiver() { }
    /* 0x0C */ virtual s32 vt_0C() = 0;
    /* 0x10 */ virtual s32 vt_10(int arg0) = 0;
    /* 0x14 */ virtual s32 vt_14(int arg0, int arg1) = 0;
};

class MessageReceiver : public IMessageReceiver {
public:
    MessageReceiver();

    /* 0x08 */ virtual ~MessageReceiver();
    /* 0x0C */ virtual s32 vt_0C();
    /* 0x10 */ virtual s32 vt_10(int arg0);
    /* 0x14 */ virtual s32 vt_14(int arg0, int arg1);
};

#endif
