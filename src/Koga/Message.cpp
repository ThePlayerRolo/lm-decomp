#include "Koga/Message.hpp"
#include "dolphin/types.h"

dummy_float_data()

MessageReceiver::MessageReceiver() {}

MessageReceiver::~MessageReceiver() {}

BOOL MessageReceiver::vt_0C(ToolDataRef* param_1) { return 0; }

BOOL MessageReceiver::vt_10(ToolDataRef* param_1) { return 0; }

BOOL MessageReceiver::vt_14(ToolDataRef* param_1, char* param_2) { return 0; }

//https://decomp.me/scratch/FS7IN
MessageSender::MessageSender() { }

//https://decomp.me/scratch/AvZyL
MessageSender::~MessageSender() { }

s32 MessageSender::vt_14(MessageCallback1 fn, int arg0) {
    s32 receiverCount = _4.getArraySize();
    MessageReceiver** instance = _4.getArray();

    for (s32 i = 0; i < receiverCount; ++instance, ++i) {
        if ((*instance->*fn)(arg0) != 0) {
            return true;
        }
    }

    return false;
}

s32 MessageSender::vt_18(MessageCallback2 fn, int arg0, int arg1) {
    s32 receiverCount = _4.getArraySize();
    MessageReceiver** instance = _4.getArray();

    for (s32 i = 0; i < receiverCount; ++instance, ++i) {
        if ((*instance->*fn)(arg0, arg1) != 0) {
            return true;
        }
    }

    return false;
}

bool MessageSender::addReceiver(void* receiver) {
    if (_4.getArraySize() < 12) {
        _4.add((MessageReceiver**)&receiver);
        return true;
    }

    return false;
}
