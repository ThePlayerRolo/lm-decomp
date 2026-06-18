#include "jaudio/dvdthread.h"
#include <dolphin/ar.h>
#include <dolphin/os.h>
#include "jaudio/aictrl.h"
#include "jaudio/sample.h"
#include <stddef.h>
#include <string.h>

static char audio_root_path[32] = "";

static OSMessageQueue mq;
static s32 msgbuf[0x80];
static u8 CALLSTACK[0x8000];

static u32 mq_init;
static size_t buffersize;
static u32 buffers;
static size_t next_buffersize;
static u8* next_buffertop;
static u32 next_buffers;

static OSThreadQueue dvdt_sleep;
static BOOL DVDT_PAUSE_FLAG;

static ErrorCallback error_callback;

static u32 cur_q;
static s8 lbl_804D93C4;

static u8* ADVD_BUFFER[2];
static u32 buffer_load;

static volatile u32 buffer_full;

static void __Alloc_DVDBuffer();
static void __UpdateBuffer();
static void __WriteBufferSize(u8*, u32, u32);


/**
 * @TODO: Documentation
 */
static s32 DVDReadMutex(DVDFileInfo* fileInfo, void* addr, s32 len, s32 offs,  char* errorArg)
{
	if (DVDT_PAUSE_FLAG == TRUE) {
		OSSleepThread(&dvdt_sleep);
	}

	while (TRUE) {
		s32 readPrioStatus = DVDReadPrio(fileInfo, addr, len, offs, 2);
		if (readPrioStatus == -1 && error_callback) {
			error_callback(errorArg, (u8*)addr);
			continue;
		}

		return readPrioStatus;
	}
}

/**
 * @TODO: Documentation
 */
void DVDT_ExtendPath(char* dst,  char* ext)
{
	if (*audio_root_path != '\0') {
		strcpy(dst, audio_root_path);
		if (*ext == '/') {
			strcat(dst, ext + 1);
		} else {
			strcat(dst, ext);
		}
	} else {
		strcpy(dst, ext);
	}
}

/**
 * @TODO: Documentation
 */
s32 DVDT_AddTask(TaskCallback callback, void* stack, size_t len)
{

	if (lbl_804D93C4 == false) {
		cur_q = 0;
		lbl_804D93C4 = 1;
	}

	if (mq_init == FALSE) {
		return 0;
	}

	TaskCallback* cstack;
	BOOL enable = OSDisableInterrupts();

	cstack =  (TaskCallback*)&CALLSTACK[cur_q++ * 0x100];

	if (cur_q == 0x80) {
		cur_q = 0;
	}

	OSRestoreInterrupts(enable);

	Jac_bcopy(stack, cstack + 1, len);

	*cstack = callback;
	OSSendMessage(&mq, (OSMessage)cstack, OS_MESSAGE_BLOCK);

	return 1;
}

/**
 * @TODO: Documentation
 */
void jac_dvdproc_init()
{
	OSInitMessageQueue(&mq, (OSMessage*)msgbuf, ARRAY_SIZE(msgbuf));
	mq_init = 1;
}

/**
 * @TODO: Documentation
 */
void* jac_dvdproc(void*)
{
	__Alloc_DVDBuffer();
	TaskCallback* callback;

	u8* buf = (u8*)OSAlloc2(0x10000);

	OSInitThreadQueue(&dvdt_sleep);
	OSMessage msg;
	while (TRUE) {
		while (TRUE) {
			OSReceiveMessage(&mq, &msg, OS_MESSAGE_BLOCK);
			callback = (TaskCallback*)msg;
			__UpdateBuffer();

			if (buffersize == 0) {
				__WriteBufferSize(buf, 2, 0x8000);
			}
			if (callback != nullptr) {
				break;
			};
		}
		(*callback)(callback + 1);
	}
}

/**
 * @TODO: Documentation
 */
static void __DoError(DVDCall* call, u32)
{
	if (call->callbackStatus != nullptr) {
		*call->callbackStatus = -1;
	}

	if (call->callback != nullptr) {
		call->callback(-1);
	}
}

/**
 * @TODO: Documentation
 */
static void __DoFinish(DVDCall* call, u32 status)
{
	if (call->callbackStatus != nullptr) {
		*call->callbackStatus = status;
	}

	if (call->callback != nullptr) {
		call->callback(call->owner);
	}
}

/**
 * @TODO: Documentation
 */
static void __DVDT_CheckBack(void* cb)
{
	DVDCall* callback = (DVDCall*)cb;

	__DoFinish(callback, callback->owner);
}

/**
 * @TODO: Documentation
 */
s32 DVDT_LoadtoDRAM_Main(void* dvdCall)
{
	s32 readStatus = 0;
	DVDCall* call  = (DVDCall*)dvdCall;

	DVDFileInfo finfo;

	if (DVDOpen(call->fileName, &finfo) == FALSE) {
		__DoError(call, 0);
		return -1;
	}
	u32 infoLength = finfo.length;
	if (infoLength == 0) {
		__DoError(call, 1);
		return -1;
	}

	if (call->length == 0) {
		call->length = infoLength;
	}

	DCInvalidateRange((void*)call->dst, call->length);
	readStatus |= DVDReadMutex(&finfo, (void*)call->dst, call->length, call->src, call->fileName);
	DVDClose(&finfo);
	__DoFinish(call, readStatus);
	return 0;
}

/**
 * @TODO: Documentation
 */
s32 DVDT_LoadtoDRAM(u32 owner,  char* name, u32 dst, u32 src, u32 length, u32* status, Jac_DVDCallback callback)
{
	DVDCall call;
	DVDCall* pCall = &call;
	pCall->owner   = owner;
	DVDT_ExtendPath(pCall->fileName, name);

	pCall->dst            = dst;
	pCall->callbackStatus = status;

	if (status) {
		*status = 0;
	}
	pCall->callback = callback;
	pCall->src      = src;
	pCall->length   = length;

	DVDT_AddTask(&DVDT_LoadtoDRAM_Main, (void*)pCall, sizeof(DVDCall));
	return 0;
}

/**
 * @TODO: Documentation
 */
static void __Alloc_DVDBuffer()
{
	if (buffersize == 0) {
		int i;

		for (i = 0; i < buffers; i++) {
			ADVD_BUFFER[i] = 0;
		}
	}
}

/**
 * @TODO: Documentation
 */
static void __WriteBufferSize(u8* buf, u32 numBuffers, u32 size)
{
	buffersize = size;
	buffers    = numBuffers;

	int i;
	int j = numBuffers;

	for (i = 0; i < numBuffers; i++, j--) {
		ADVD_BUFFER[i] = buf;
		buf += size;
	}
}

/**
 * @TODO: Documentation
 */
static void __UpdateBuffer()
{
	if (next_buffers != 0) {
		__WriteBufferSize(next_buffertop, next_buffers, next_buffersize);
		next_buffers   = 0;
		next_buffertop = nullptr;
	}
}


/**
 * @TODO: Documentation
 */
static void ARAM_DMAfinish(u32)
{
	buffer_full--;
}

/**
 * @TODO: Documentation
 */
s32 DVDT_LoadtoARAM_Main(void* dvdCall)
{
	DVDCall* call        = (DVDCall*)dvdCall;
	static int arq_index = 0;
	static DVDFileInfo finfo;
	static ARQRequest req[4];

	if (!DVDOpen(call->fileName, &finfo)) {
		__DoError(call, 0);
		return -1;
	}

	u32 len = finfo.length;
	if (len == 0) {
		__DoError(call, 1);
		return -1;
	}

	if (call->length == 0) {
		call->length = len;
	}

	while (call->length != 0) {
		u32 readSize;
		u8* buf     = ADVD_BUFFER[buffer_load];
		buffer_load = (buffer_load + 1) % buffers;
		while (buffer_full == buffers)
			;

		if (call->length < buffersize) {
			readSize = ALIGN_NEXT(call->length, 32);
			len      = DVDReadMutex(&finfo, buf, readSize, call->src, call->fileName);

			call->length = 0;
		} else {
			readSize = buffersize;
			len      = DVDReadMutex(&finfo, buf, readSize, call->src, call->fileName);

			call->src += buffersize;
			call->length -= buffersize;
		}

		ARQPostRequest(&req[arq_index], 0x12345678, ARQ_TYPE_MRAM_TO_ARAM, ARQ_PRIORITY_HIGH, (u32)buf, call->dst, readSize,
		               ARAM_DMAfinish);
		buffer_full++;
		arq_index++;
		arq_index &= 3;
		call->dst += readSize;
	}

	DVDClose(&finfo);

	while (buffer_full != 0)
		;

	__DoFinish(call, len);

	return 0;
}

#ifdef BUILD_MATCHING
//this was probably some local bss that was stripped out of the final build so we do this instead!
static u8 lbl_8043D14C[0x5C];
#endif

/**
 * @TODO: Documentation
 */
s32 DVDT_LoadtoARAM(u32 owner,  char* path, u32 dst, u32 src, u32 length, u32* status, Jac_DVDCallback callback)
{
	DVDCall call;
	DVDCall* pCall = &call;

	pCall->owner = owner;
	DVDT_ExtendPath(pCall->fileName, path);

	pCall->dst            = dst;
	pCall->callbackStatus = status;
	if (status != 0) {
		*status = 0;
	}

	pCall->callback = callback;
	pCall->src      = src;
	pCall->length   = length;

	DVDT_AddTask(DVDT_LoadtoARAM_Main, pCall, 0x58);

	return 0;
}

/**
 * @TODO: Documentation
 */
s32 DVDT_CheckFile(char* file)
{
	char path[64];
	char** REF_file = &file;
	static DVDFileInfo finfo;

	DVDT_ExtendPath(path, file);

	if (!DVDOpen(path, &finfo)) {
		return 0;
	}
	u32 len = finfo.length;

	DVDClose(&finfo);
	return len;
}

/**
 * @TODO: Documentation
 */
s32 DVDT_LoadFile(char* file, u8* p2)
{
	volatile u32 status           = 0;
	char** REF_file = &file;
	STACK_PAD_VAR(2);
	DVDT_LoadtoDRAM(0, file, (u32)p2, 0, 0, (u32*)&status, nullptr);

	while (status == 0) { }

	if (status == -1) {
		return 0;
	}

	return status;
}

/**
 * @TODO: Documentation
 */
void DVDT_CheckPass(u32 owner, u32* status, Jac_DVDCallback callback)
{
	DVDCall call;
	void* cb = (void*)&call;

	call.owner          = owner;
	call.callbackStatus = status;
	call.callback       = callback;

	DVDT_AddTask((TaskCallback)__DVDT_CheckBack, cb, 0x58);
}

/**
 * @TODO: Documentation
 * @note UNUSED Size: 000064
 */
BOOL Jac_CheckFile(char* file)
{
	static DVDFileInfo finfo;
	char** REF_file = &file;

	if (!DVDOpen(file, &finfo)) {
		return FALSE;
	}

	u32 len = finfo.length;
	DVDClose(&finfo);

	return len;
}

s32 Jac_LoadFile(char* file, u8* p2)
{
	static DVDFileInfo finfo;
	char** REF_file = &file;

	if (!DVDOpen(file, &finfo)) {
		return 0;
	}

	s32 length = finfo.length;

	while (TRUE) {
		s32 readPrioStatus = DVDReadPrio(&finfo, p2, length, 0, 2);
		if (readPrioStatus == -1 && error_callback) {
			error_callback(file, (u8*)p2);
			continue;
		}
		break;
	}

	DVDClose(&finfo);
	return length;

}

void DVDT_Pause()
{
	DVDT_PAUSE_FLAG = TRUE;
}

void DVDT_UnPause()
{
	if (DVDT_PAUSE_FLAG == TRUE) {
		OSWakeupThread(&dvdt_sleep);

	}
	DVDT_PAUSE_FLAG = FALSE;
}
