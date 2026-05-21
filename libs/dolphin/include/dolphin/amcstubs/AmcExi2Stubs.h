#include <dolphin/os/OSInterrupt.h>

// EXI error codes
typedef enum
{
	AMC_EXI_NO_ERROR	= 0,
	AMC_EXI_UNSELECTED
} AmcExiError;

void EXI2_Init(volatile u8**, __OSInterruptHandler);
void EXI2_EnableInterrupts();
u32 EXI2_Poll();
int EXI2_ReadN(void*, u32);
int EXI2_WriteN();
void EXI2_Reserve();
void EXI2_Unreserve();
int AMC_IsStub();
