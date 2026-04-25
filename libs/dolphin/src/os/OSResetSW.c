#include <dolphin.h>
#include <dolphin/os.h>

#include <dolphin/internal/__os.h>

u8 GameChoice AT_ADDRESS(OS_BASE_CACHED | 0x30E3);
static OSResetCallback ResetCallback;
static BOOL Down;
static BOOL LastState;
static OSTime HoldUp;
static OSTime HoldDown;

void __OSResetSWInterruptHandler(__OSInterrupt exception, struct OSContext *context) {
	OSResetCallback callback;

	HoldDown = __OSGetSystemTime();
	while (__OSGetSystemTime() - HoldDown < OSMicrosecondsToTicks(100)
	       && !(__PIRegs[0] & 0x00010000)) {
		;
	}
	if (!(__PIRegs[0] & 0x00010000)) {
		LastState = Down = TRUE;
		__OSMaskInterrupts(OS_INTERRUPTMASK_PI_RSW);
		if (ResetCallback) {
			callback      = ResetCallback;
			ResetCallback = NULL;
			callback();
		}
	}
	__PIRegs[0] = 2;
}

BOOL OSGetResetSwitchState() {
    BOOL enabled = OSDisableInterrupts();
    BOOL state;
    u32  reg = __PIRegs[0];

    if (!(reg & 0x00010000))
    {
        if (!Down)
        {
            Down = TRUE;
            state = HoldUp ? TRUE : FALSE;
            HoldDown = __OSGetSystemTime();
        }
        else
        {
            state = (HoldUp || (OSMicrosecondsToTicks (100) < __OSGetSystemTime() - HoldDown))
                        ? TRUE
                        : FALSE;
        }
    }
    else if (Down)
    {
        Down = FALSE;
        state = LastState;
        if (state)
        {
            HoldUp = __OSGetSystemTime();
        }
    }
    else if (HoldUp && (__OSGetSystemTime() - HoldUp < OSMillisecondsToTicks (40)))

    {
        state = TRUE;
    }
    else
    {
        state = FALSE;
        HoldUp = 0;
    }

    LastState = state;

    OSRestoreInterrupts (enabled);

    return state;
}
