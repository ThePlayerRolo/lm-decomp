#include "Os/dolphin/targcont.h"
#include "Os/dolphin/dolphin_trk_glue.h"
#include "ppc/Generic/targimpl.h"

DSError TRKTargetContinue(void)
{
	TRKTargetSetStopped(0);
	UnreserveEXI2Port();
	TRKSwapAndGo();
	ReserveEXI2Port();
	return 0;
}
