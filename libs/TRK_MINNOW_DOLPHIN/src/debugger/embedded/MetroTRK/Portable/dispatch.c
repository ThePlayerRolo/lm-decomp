#include "MetroTRK/Portable/dispatch.h"
#include "MetroTRK/Portable/msgbuf.h"
#include "MetroTRK/Portable/msghndlr.h"

u32 gTRKDispatchTableSize;

struct DispatchEntry {
	int (*fn)(TRKBuffer*);
};

struct DispatchEntry gTRKDispatchTable[33] = {
	{ &TRKDoUnsupported },   { &TRKDoConnect },        { &TRKDoDisconnect },
	{ &TRKDoReset },         { &TRKDoVersions },       { &TRKDoSupportMask },
	{ &TRKDoCPUType },       { &TRKDoUnsupported },    { &TRKDoUnsupported },
	{ &TRKDoUnsupported },   { &TRKDoUnsupported },    { &TRKDoUnsupported },
	{ &TRKDoUnsupported },   { &TRKDoUnsupported },    { &TRKDoUnsupported },
	{ &TRKDoUnsupported },   { &TRKDoReadMemory },     { &TRKDoWriteMemory },
	{ &TRKDoReadRegisters }, { &TRKDoWriteRegisters }, { &TRKDoUnsupported },
	{ &TRKDoUnsupported },   { &TRKDoFlushCache },     { &TRKDoUnsupported },
	{ &TRKDoContinue },      { &TRKDoStep },           { &TRKDoStop },
	{ &TRKDoUnsupported },   { &TRKDoUnsupported },    { &TRKDoUnsupported },
	{ &TRKDoUnsupported },   { &TRKDoUnsupported },
};

DSError TRKInitializeDispatcher()
{
	gTRKDispatchTableSize = 32;
	return DS_NoError;
}

DSError TRKDispatchMessage(TRKBuffer* buffer)
{
	DSError error;
	u8 command;

	error = DS_DispatchError;
	TRKSetBufferPosition(buffer, 0);
	TRKReadBuffer1_ui8(buffer, &command);
	if (command < gTRKDispatchTableSize) {
		error = gTRKDispatchTable[command].fn(buffer);
	}
	return error;
}
