#include "jaudio/aramcall.h"

#include "jaudio/dummyrom.h"
#include "jaudio/dvdthread.h"
#include "jaudio/heapctrl.h"

#include <stddef.h>
#include <string.h>

jaheap_ aram_mother;

ARAMCallback ARCALL    = &LoadAram_Default;
static char extdir[64] = "/Banks/";

/**
 * @TODO: Documentation
 * @note UNUSED Size: 000008
 */
void Jac_RegisterARAMCallback(ARAMCallback callback)
{
	ARCALL = callback;
}

/**
 * @TODO: Documentation
 */
u32 LoadAram(char* filepath, u32* status, u32 dst)
{
	 char** REF_filepath = &filepath;
	u32* REF_dst              = &dst;

	if (DVDT_LoadtoARAM(0, filepath, dst, 0, 0, status, nullptr) == -1) {
		return 0;
	}
	return dst;
}

/**
 * @TODO: Documentation
 */
u32 LoadAramSingle(char* filepath, u32 src, u32 length, u32* status, u32 dst)
{
	STACK_PAD_VAR(1);
	 char** REF_filepath = &filepath;
	u32* REF_src              = &src;
	u32* REF_length           = &length;

	if (DVDT_LoadtoARAM(0, filepath, dst, src, length, status, nullptr) == -1) {
		return 0;
	}
	return dst;
}

/**
 * @TODO: Documentation
 * @note UNUSED Size: 000030
 */
void Jac_WaveDirectorySet(char* directory)
{
	strcpy(extdir, directory);
}

/**
 * @TODO: Documentation
 * @note UNUSED Size: 00000C
 */
jaheap_* Get_AramMotherHeap(void)
{
	return &aram_mother;
}

/**
 * @TODO: Documentation
 */
void Show_AramMotherHeap(void)
{
	Jac_ShowHeap(&aram_mother, 0);
}

/**
 * @TODO: Documentation
 */
void Collect_AramMotherHeap(void)
{
	Jac_GarbageCollection_St(&aram_mother);
	Show_AramMotherHeap();
}

/**
 * @TODO: Documentation
 */
u32 LoadAram_Default(char* filename, u32 src, u32 length, u32* status, jaheap_* heap)
{
	char filepath[130];

	u32 outSize;

	static BOOL inited = TRUE;
	if (inited) {
		inited = FALSE;

		Jac_InitMotherHeap(&aram_mother, (u32)ARAllocFull(&outSize), outSize, 0);
	}

	strcpy(filepath, extdir);
	strcat(filepath, filename);

	if (src == 0 && length == 0) {
		if (!Jac_AllocHeap(heap, &aram_mother, DVDT_CheckFile(filepath))) {
			return 0;
		}
		return LoadAram(filepath, status, heap->startAddress);
	} else {
		if (!Jac_AllocHeap(heap, &aram_mother, length)) {
			return 0;
		}
		return LoadAramSingle(filepath, src, length, status, heap->startAddress);
	}
}

/**
 * @TODO: Documentation
 */
u32 LoadAram_All(char* filename, u32* status, jaheap_* heap)
{
	return ARCALL(filename, 0, 0, status, heap);
}

/**
 * @TODO: Documentation
 */
u32 LoadAram_One(char* filename, u32 src, u32 length, u32* status, jaheap_* heap)
{
	return ARCALL(filename, src, length, status, heap);
}
