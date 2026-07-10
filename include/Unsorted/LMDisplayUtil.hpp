#ifndef _80007398_H_
#define _80007398_H_

#include <types.h>

struct LMVISettings {
    /* 0x0 */ u16 _0;
    /* 0x2 */ bool _2;
    /* 0x3 */ u8 _3;
};

void LMInitDisplay();
void fn_80007800();
void LMChangeFrameBuffer();
void LMDefaultOrthoView();
void LMSetViewportJitter(f32 left, f32 top, f32 width, f32 height, f32 near, f32 far);
void fn_80007E50(u16);
void fn_80007E60(s32);
void fn_80007E70(bool);
void* LMGetMainFrameBuffer();
void* LMGetPrevMainFrameBuffer();
u32 LMGetVIMessageQueueUnk4();
void LMSetIntRenderModeVFilter(u8 vfilterVal);

// Progressive mode related functions start
void fn_80007F28();
void fn_80007F90();
void fn_80008004();
void LMUpdateProgressiveMode();
// Progressive mode related functions end

#endif
