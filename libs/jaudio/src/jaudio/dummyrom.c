#include "jaudio/dummyrom.h"
#include "Dolphin/ar.h"
#include "Dolphin/os.h"
#include "jaudio/audiocommon.h"
#include "jaudio/memory.h"

//Todo: is this somewhere else?
ALHeap aram_hp;
static u32 AUDIO_ARAM_TOP;

/* All four of these are unused besides like one mention? */
static u32 lbl_804D9344;
static u32 lbl_804D9348;
static u32 lbl_804D934C;
static u32 lbl_804D9350;

static u32 CARD_SECURITY_BUFFER;
u8* JAC_ARAM_DMA_BUFFER_TOP;
static u32 SELECTED_ARAM_SIZE;

/**
 * @TODO: Documentation
 * @note UNUSED Size: 000008
 */
void GetNeosRomTop()
{
	// UNUSED FUNCTION
}

/**
 * @TODO: Documentation
 * @note UNUSED Size: 000028
 */
void mesg_finishcall(u32)
{
	// UNUSED FUNCTION
}

/**
 * @TODO: Documentation
 * @note UNUSED Size: 00005C
 */
void ARAMStartDMAmesg(u32, u32, u32, u32, s32, OSMessageQueue*)
{
	// UNUSED FUNCTION
}

/**
 * @TODO: Documentation
 * @note UNUSED Size: 00004C
 */
void ARAMStartDMA(u32, u32, u32, u32, s32, u32*, void (*)())
{
	// UNUSED FUNCTION
}

/**
 * @TODO: Documentation
 */
void Jac_SetAudioARAMSize(u32 size)
{
	SELECTED_ARAM_SIZE = size;
}


void* ARAlloc2(u32 param_1)
{
	void* alloc = Nas_HeapAlloc(&aram_hp, param_1);

	return alloc;

}

/**
 * @TODO: Documentation
 */
void* ARAllocFull(u32* outSize)
{
	u32 freeSize = aram_hp.length - ((int)aram_hp.current - (int)aram_hp.base);

	void* alloc = Nas_HeapAlloc(&aram_hp, freeSize - 32);
	*outSize    = freeSize - 32;

	return alloc;
}

/**
 * @TODO: Documentation
 */
void Jac_InitARAM(u32 loadAudiorom)
{
	volatile u32 audiorom_size;
	u32 aram_size;

	if (SELECTED_ARAM_SIZE) {
		aram_size = SELECTED_ARAM_SIZE;
	} else {
		aram_size = AUDIO_ARAM_SIZE;
	}

	AUDIO_ARAM_TOP = ARGetBaseAddress();

	lbl_804D9344 =  lbl_804D9348 = audiorom_size  = 0;


	CARD_SECURITY_BUFFER = 0x40;
	audiorom_size += AUDIO_ARAM_TOP;
	JAC_ARAM_DMA_BUFFER_TOP = (u8*)audiorom_size;
	audiorom_size += AUDIO_ARAM_HEAP_SIZE;
	Nas_HeapInit(&aram_hp, (u8*)audiorom_size, aram_size - audiorom_size);

	/* Probably leftovers from some debug print statement */
	(void)audiorom_size;
	STACK_PAD_VAR(6);
}
