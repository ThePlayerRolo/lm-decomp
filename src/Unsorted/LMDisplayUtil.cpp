#include "Unsorted/LMDisplayUtil.hpp"
#include "Unsorted/80005EB8.hpp"
#include "Unsorted/GamePad.hpp"
#include <JSystem/JKernel/JKRExpHeap.hpp>
#include <JSystem/JUtility/JUTDirectPrint.hpp>
#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/vi.h>

// externs
extern void fn_80047444(s32);

struct LMVIMessageQueue {
    /* 0x00 */ u32 _0;
    /* 0x04 */ u32 _4;
    /* 0x08 */ OSMessageQueue mMessageQueue;
    /* 0x28 */ s32 mMsgArr[1];  // Msg
};

// .bss start
LMVIMessageQueue sVIMessageQueue;
GXRenderModeObj sIntRenderModeObj;
// .bss end

// .data start
GXRenderModeObj sProgRenderModeObj = {VI_TVMODE_NTSC_PROG,
                                      640,
                                      480,
                                      480,
                                      40,
                                      0,
                                      640,
                                      480,
                                      VI_XFBMODE_SF,
                                      0,
                                      0,
                                      {
                                          {
                                              6,
                                              6,
                                          },
                                          {
                                              6,
                                              6,
                                          },
                                          {
                                              6,
                                              6,
                                          },
                                          {
                                              6,
                                              6,
                                          },
                                          {
                                              6,
                                              6,
                                          },
                                          {
                                              6,
                                              6,
                                          },
                                          {
                                              6,
                                              6,
                                          },
                                          {
                                              6,
                                              6,
                                          },
                                          {
                                              6,
                                              6,
                                          },
                                          {
                                              6,
                                              6,
                                          },
                                          {
                                              6,
                                              6,
                                          },
                                          {
                                              6,
                                              6,
                                          },
                                      },
                                      {0, 0, 26, 12, 26, 0, 0}};

Vec lbl_8021DA40 = {0, 0, 0};

Mtx sDefaultMtx = {{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}};
// .data end

// .sbss start
s32 lbl_804D8030;
u8 sRenderMode;
LMVISettings sVISettings;
void* lbl_804D803C;
void* lbl_804D8040;
void* sMainFrameBuffer;
void* sPrevMainFrameBuffer;
void* lbl_804D804C[2];
GXRenderModeObj* sCurRenderModeObj;
s32 lbl_804D8058;
s32 sProgressiveMode;
s32 lbl_804D8060;
// .sbss end

// .sdata start
GXRenderModeObj* sDefaultRenderModes[2] = {
    &sIntRenderModeObj,
    &sProgRenderModeObj,
};
// .sdata end

static void LMConfigureRenderDisplay();
static void postRetraceCallback(u32 retraceCount);

void LMInitDisplayInternal(LMVISettings* dst) {
    VISetBlack(TRUE);
    sIntRenderModeObj = GXNtsc480IntDf;
    sIntRenderModeObj.vfilter[0] = 6;
    sIntRenderModeObj.vfilter[1] = 0;
    sIntRenderModeObj.vfilter[5] = 0;
    sIntRenderModeObj.vfilter[6] = 6;
    sIntRenderModeObj.vfilter[2] = 20;
    sIntRenderModeObj.vfilter[3] = 12;
    sIntRenderModeObj.vfilter[4] = 20;
    OSGetTime();

    u32 uVar1 = 1;

    OSInitMessageQueue(&sVIMessageQueue.mMessageQueue, &sVIMessageQueue.mMsgArr, ARRAY_COUNT(sVIMessageQueue.mMsgArr));
    sVIMessageQueue._0 = VIGetRetraceCount();
    sVIMessageQueue._4 = 1;
    u8 groupID = 2;

    dst->_0 = 0;
    dst->_2 = true;
    dst->_3 = 0;
    sMainFrameBuffer = nullptr;
    lbl_804D8014->changeGroupID(groupID);

    u32 frameBufferSize = 0x96000;
    if (lbl_804D803C == nullptr) {
        uVar1 = 0;

        lbl_804D803C = JKRAllocFromHeap(nullptr, frameBufferSize, 0x20);
    }

    if (lbl_804D803C != nullptr) {
        DCInvalidateRange(lbl_804D803C, frameBufferSize);
    }

    if (dst->_2 == true) {
        if (lbl_804D8040 == nullptr) {
            uVar1 = 0;

            lbl_804D8040 = JKRAllocFromHeap(nullptr, frameBufferSize, 0x20);
        }

        if (lbl_804D8040 != nullptr) {
            DCInvalidateRange(lbl_804D8040, frameBufferSize);
        }
        sMainFrameBuffer = lbl_804D803C;
    } else {
        lbl_804D8040 = sMainFrameBuffer = lbl_804D803C;
    }

    lbl_804D804C[0] = lbl_804D803C;
    void* temp = sMainFrameBuffer;
    lbl_804D804C[1] = lbl_804D8040;

    VISetNextFrameBuffer(temp);
    sCurRenderModeObj = &sIntRenderModeObj;
    LMConfigureRenderDisplay();
    // Temp to match stack, its possible they used this for debugging
    VIRetraceCallback cb = VISetPostRetraceCallback(postRetraceCallback);

    lbl_804D8014->changeGroupID(26);
}

void postRetraceCallback(u32 retraceCount) {
    if (retraceCount - sVIMessageQueue._0 >= sVIMessageQueue._4) {
        OSSendMessage(&sVIMessageQueue.mMessageQueue, (void*)0x444F4E45, OS_MESSAGE_NOBLOCK);
    }
}

static void setNextVIFrameBuffer(LMVISettings* pSettings) {
    // TODO: Remove this
    FORCE_DONT_INLINE;
    if ((pSettings->_0 & 1)) {
        VISetBlack(GX_FALSE);
    } else {
        VISetBlack(GX_TRUE);
    }

    VISetNextFrameBuffer(sMainFrameBuffer);
    VIFlush();
    if (pSettings->_2) {
        pSettings->_3 ^= 1;
        sMainFrameBuffer = lbl_804D804C[pSettings->_3];
    }
}

void LMResetRenderDisplay() {
    GXColor clearColor = {0, 0, 0, 0};
    GXSetCopyClear(clearColor, 0xFFFFFF);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_TRUE);
    GXSetDispCopySrc(0, 0, sCurRenderModeObj->fbWidth, sCurRenderModeObj->efbHeight);
    GXSetDispCopyDst(sCurRenderModeObj->fbWidth, sCurRenderModeObj->efbHeight);
    GXSetDispCopyYScale((f32)sCurRenderModeObj->xfbHeight / (f32)sCurRenderModeObj->efbHeight);
    GXSetCopyFilter(sCurRenderModeObj->aa, sCurRenderModeObj->sample_pattern, GX_TRUE, sCurRenderModeObj->vfilter);
    GXSetCopyClamp((GXFBClamp)(GX_CLAMP_TOP | GX_CLAMP_BOTTOM));
    GXSetDispCopyGamma(GX_GM_1_0);
    if (sCurRenderModeObj->aa) {
        GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
        GXSetDither(GX_FALSE);
    } else {
        GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
        GXSetDither(GX_TRUE);
    }
}

static void LMConfigureRenderDisplay() {
    VIConfigure(sCurRenderModeObj);
    LMResetRenderDisplay();
    GXCopyDisp(sMainFrameBuffer, GX_TRUE);
    GXCopyDisp(sMainFrameBuffer, GX_TRUE);
    GXFlush();
    GXDrawDone();
    VIFlush();
    VIWaitForRetrace();
    VIWaitForRetrace();
}

void LMInitDisplay() {
    LMInitDisplayInternal(&sVISettings);
}

void fn_80007800() {
    GXInvalidateTexAll();
    GXInvalidateVtxCache();
    GXSetScissor(0, 0, sCurRenderModeObj->fbWidth, sCurRenderModeObj->xfbHeight);
}

void fn_8000783C() {
    GXDrawDone();
    OSReceiveMessage(&sVIMessageQueue.mMessageQueue, nullptr, OS_MESSAGE_BLOCK);
    sVIMessageQueue._0 = VIGetRetraceCount();
    VIWaitForRetrace();
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);

    if (sMainFrameBuffer != nullptr) {
        GXCopyDisp(sMainFrameBuffer, GX_TRUE);
    }

    if ((sVISettings._0 & 1)) {
        VISetBlack(GX_FALSE);
    } else {
        VISetBlack(GX_TRUE);
    }

    VISetNextFrameBuffer(sMainFrameBuffer);
    VIFlush();

    if (sVISettings._2) {
        sVISettings._3 ^= 1;
        sMainFrameBuffer = lbl_804D804C[sVISettings._3];
    }

    GXFlush();
}

void LMChangeFrameBuffer() {
    LMResetRenderDisplay();
    if (sVISettings._2 == true) {
        GXDrawDone();
        GXSetColorUpdate(GX_TRUE);
        GXSetAlphaUpdate(GX_TRUE);
        GXCopyDisp(sMainFrameBuffer, GX_TRUE);
        GXFlush();
        setNextVIFrameBuffer(&sVISettings);
        OSReceiveMessage(&sVIMessageQueue.mMessageQueue, NULL, OS_MESSAGE_BLOCK);
        sVIMessageQueue._0 = VIGetRetraceCount();
    } else {
        fn_8000783C();
    }
    void* frameBuf = sMainFrameBuffer;

    JUTDirectPrint::getManager()->changeFrameBuffer(frameBuf, 640, 480);
}

void fn_800079B0() {
    if (sCurRenderModeObj != sDefaultRenderModes[sRenderMode]) {
        sCurRenderModeObj = sDefaultRenderModes[sRenderMode];
        LMConfigureRenderDisplay();
    }
}

// https://decomp.me/scratch/d7YKn
void LMDefaultOrthoView() {
    GXSetScissor(0, 0, sCurRenderModeObj->fbWidth, sCurRenderModeObj->xfbHeight);
    GXSetViewportJitter(0.0f, 0.0f, sCurRenderModeObj->fbWidth, sCurRenderModeObj->xfbHeight, 0.0f, 1.875f, 1);
    Mtx orthoMtx;
    MTXOrtho(orthoMtx, -0.0f, 3.96875f, -0.0f, sCurRenderModeObj->fbWidth, -1.875f, 4.4765625f);
    GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);
    GXSetCullMode(GX_CULL_NONE);
    GXLoadPosMtxImm(sDefaultMtx, 0);
    GXLoadNrmMtxImm(sDefaultMtx, 0);
    GXLoadTexMtxImm(sDefaultMtx, 60, GX_MTX2x4);
    GXSetCurrentMtx(0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_RGBA4, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_RGBX8, 15);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_CLR_RGBA, GX_RGBX8, 15);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXColor local_70 = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanMatColor(GX_COLOR0A0, local_70);
    GXColor local_74 = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanAmbColor(GX_COLOR0A0, local_74);
    GXColor local_78 = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanMatColor(GX_COLOR1A1, local_78);
    GXColor local_7c = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanAmbColor(GX_COLOR1A1, local_7c);
    GXColor local_80 = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetTevKColor(GX_KCOLOR0, local_80);
    GXSetTevKColorSel(GX_TEVSTAGE0, GX_TEV_KCSEL_K0);
    GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_K0_A);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60, GX_FALSE, 125);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetZCompLoc(GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_GREATER, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetDstAlpha(GX_FALSE, 0xFF);
}

// https://decomp.me/scratch/tMgJK
void LMSetViewportJitter(f32 left, f32 top, f32 width, f32 height, f32 near, f32 far) {
    f32 widthScale = sCurRenderModeObj->fbWidth / 640.0f;

    if (sCurRenderModeObj->field_rendering) {
        GXSetViewportJitter(left * widthScale, top * -1.0f, width * widthScale, height * -1.0f, near, far, VIGetNextField());
    } else {
        GXSetViewportJitter(left * widthScale, top * -1.0f, width * widthScale, height * -1.0f, near, far, 1);
    }
}

void fn_80007E50(u16 param_1) {
    sVISettings._0 |= param_1;
}

void fn_80007E60(s32 param_1) {
    sVIMessageQueue._4 = param_1;
}

// https://decomp.me/scratch/BHaSG
void fn_80007E70(bool param_1) {
    sVISettings._2 = param_1;
    if (param_1 == true) {
        sVISettings._3 ^= 1;
        sVISettings._3 &= sVISettings._0;
        sMainFrameBuffer = lbl_804D804C[sVISettings._3];
        return;
    }

    sPrevMainFrameBuffer = sMainFrameBuffer;

    if (sPrevMainFrameBuffer == lbl_804D803C)
        sMainFrameBuffer = lbl_804D8040;
    else
        sMainFrameBuffer = lbl_804D803C;
}

void* LMGetMainFrameBuffer() {
    return sMainFrameBuffer;
}

void* LMGetPrevMainFrameBuffer() {
    return sPrevMainFrameBuffer;
}

u32 LMGetVIMessageQueueUnk4() {
    return sVIMessageQueue._4;
}

// https://decomp.me/scratch/jpyvK
void LMSetIntRenderModeVFilter(u8 vfilterVal) {
    sIntRenderModeObj.vfilter[0] = vfilterVal;
    sIntRenderModeObj.vfilter[6] = vfilterVal;
    sIntRenderModeObj.vfilter[2] = 26 - vfilterVal;
    sIntRenderModeObj.vfilter[4] = 26 - vfilterVal;
}

void fn_80007F28() {
    if (VIGetDTVStatus() != 0) {
        if (sGamePad->testButton(JUTGamePad::B) != 0 || OSGetProgressiveMode() != 0) {
            lbl_804D8058 = 1;
            sProgressiveMode = 1;
            return;
        }

        OSSetProgressiveMode(0);
        return;
    }

    OSSetProgressiveMode(0);
}

void fn_80007F90() {
    if (lbl_804D8058 != 1)
        return;

    if (sGamePad->testRepeat(JUTGamePad::PRESS_LEFT)) {
        sProgressiveMode ^= 1;
    }

    if (sGamePad->testRepeat(JUTGamePad::PRESS_RIGHT)) {
        sProgressiveMode ^= 1;
    }

    fn_80047444(sProgressiveMode);
}

void fn_80008004() {
    static u32 lbl_804D8064;
    static s8 lbl_804D8068;

    if (!lbl_804D8068) {
        lbl_804D8064 = false;
        lbl_804D8068 = true;
    }

    if (lbl_804D8058 != 2)
        return;

    if (lbl_804D8060 <= 0) {
        lbl_804D8058 = 0;
        return;
    }

    lbl_804D8060 = lbl_804D8060 - 1;
    fn_80047444(sProgressiveMode + 2);
}

void LMUpdateProgressiveMode() {
    if (lbl_804D8058 != 1)
        return;

    if (sProgressiveMode == OSGetProgressiveMode()) {
        lbl_804D8060 = 0;
        lbl_804D8058 = 0;
    } else {
        lbl_804D8060 = 90;
        lbl_804D8058 = 2;
    }
    OSSetProgressiveMode(sProgressiveMode);
    sRenderMode = OSGetProgressiveMode();
}
