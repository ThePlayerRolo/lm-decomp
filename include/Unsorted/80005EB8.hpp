#ifndef _80005EB8_H_
#define _80005EB8_H_

// TODO: Could be apart of main.cpp

#include <dolphin.h>

class JKRExpHeap;

void initializeGX();
void fn_80005F10();
void* fn_80006080(u32 size, int alignment);

//Possibly JKRFree being uninlined
void fn_80006138(void* ptr);

//Frees all the groups before the groupID
void fn_8000615C(u8 groupID);

//Changes the group id for  lbl_804D8014 and lbl_804D8018 as well as setting sCurHeapGroupId (probably curGroup ID)
void fn_800061B8(u8 param_1);

u8 getCurHeapGroupId();
void fn_80006204();
s32 fn_80006228();

extern JKRExpHeap* lbl_804D8014;
extern JKRExpHeap* lbl_804D801C;

inline JKRExpHeap* get_lbl_804D8014() { return lbl_804D8014; }

#endif
