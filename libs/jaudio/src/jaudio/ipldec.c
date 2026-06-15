#include "jaudio/ipldec.h"
#include "jaudio/dspproc.h"

static u32 CUR_CMD;
static void* CUR_TASK;
static DSPCallback CUR_CALLBACK;

BOOL DspExtraTaskCheck()
{
	if (CUR_CMD != 0) {
		DiplSec(CUR_CMD);
		CUR_CMD = 0;
		if (CUR_CALLBACK != NULL) {
			CUR_CALLBACK(CUR_TASK);
			return TRUE;
		}
	}

	return FALSE;
}


void Jac_DSPcardDecodeAsync(void* task, void* cmd, DSPCallback callback)
{
	CUR_CALLBACK = callback;
	CUR_TASK = task;
	CUR_CMD = (u32)cmd;
}
