#include "Unsorted/80007398.hpp"
#include "Unsorted/80005EB8.hpp"
#include "dolphin/gx/GXTransform.h"
#include <JSystem/JKernel/JKRExpHeap.hpp>
#include <JSystem/JUtility/JUTDirectPrint.hpp>
#include <dolphin/os.h>
#include <dolphin/vi.h>
#include <dolphin/gx.h>

struct unk_lbl_803A3600 {
    u32 _0;
    s32 _4;
    OSMessageQueue mMessageQueue;
    s32 mMsgArr[1]; // Msg
};

unk_lbl_803A3600 lbl_803A3600;
GXRenderModeObj sNtscRenderModeObj;

Mtx lbl_8021DA4C = {};

GXRenderModeObj lbl_802181D0 = {
    VI_TVMODE_NTSC_PROG,
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
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
        { 6, 6, },
    },
    { 0,0, 26,12,26, 0,0  }
};

struct VISettings {
    /* 0x0 */ u16 _0;
    /* 0x2 */ bool _2;
    /* 0x3 */ u8 _3;
};

u8 lbl_804D8034;
VISettings lbl_804D8038;
void* lbl_804D803C;
void* lbl_804D8040;
void* lbl_804D8044;

void* lbl_804D804C[2];

GXRenderModeObj* lbl_804D8054;

GXRenderModeObj* lbl_804CFF70[2] = {
    &sNtscRenderModeObj,
    &lbl_802181D0,
};

void fn_80007788();
static void postRetraceCallback(u32 retraceCount);

void fn_80007398(VISettings* dst) {
    VISetBlack(TRUE);
    sNtscRenderModeObj = GXNtsc480IntDf;
    sNtscRenderModeObj.vfilter[0] = 6;
    sNtscRenderModeObj.vfilter[1] = 0;
    sNtscRenderModeObj.vfilter[5] = 0;
    sNtscRenderModeObj.vfilter[6] = 6;
    sNtscRenderModeObj.vfilter[2] = 20;
    sNtscRenderModeObj.vfilter[3] = 12;
    sNtscRenderModeObj.vfilter[4] = 20;
    OSGetTime();

    u32 uVar1 = 1;

    OSInitMessageQueue(&lbl_803A3600.mMessageQueue, &lbl_803A3600.mMsgArr, ARRAY_COUNT(lbl_803A3600.mMsgArr));
    lbl_803A3600._0 = VIGetRetraceCount();
    lbl_803A3600._4 = 1;
    u8 groupID = 2;

    dst->_0 = 0;
    dst->_2 = true;
    dst->_3 = 0;
    lbl_804D8044 = nullptr;
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
        lbl_804D8044 = lbl_804D803C;
    } else {
        lbl_804D8040 = lbl_804D8044 = lbl_804D803C;
    }

    lbl_804D804C[0] = lbl_804D803C;
    void* temp  = lbl_804D8044;
    lbl_804D804C[1] = lbl_804D8040;

    VISetNextFrameBuffer(temp);
    lbl_804D8054 = &sNtscRenderModeObj;
    fn_80007788();
    //Temp to match stack, its possible they used this for debugging
    VIRetraceCallback cb = VISetPostRetraceCallback(postRetraceCallback);

    lbl_804D8014->changeGroupID(26);
}

void postRetraceCallback(u32 retraceCount) {
  if (retraceCount - lbl_803A3600._0 >= lbl_803A3600._4) {
    OSSendMessage(&lbl_803A3600.mMessageQueue, (void *)0x444F4E45, OS_MESSAGE_NOBLOCK);
  }
}

void fn_800075EC(VISettings* pSettings) {
    //TODO: Remove this
    FORCE_DONT_INLINE;
    if ((pSettings->_0 & 1)) {
        VISetBlack(GX_FALSE);
    } else {
        VISetBlack(GX_TRUE);
    }

    VISetNextFrameBuffer(lbl_804D8044);
    VIFlush();
    if (pSettings->_2) {
        pSettings->_3 ^= 1;
        lbl_804D8044 = lbl_804D804C[pSettings->_3];
    }
}

void fn_8000766C() {
    GXColor clearColor = {0,0,0,0};
    GXSetCopyClear(clearColor, 0xFFFFFF);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_TRUE);
    GXSetDispCopySrc(0, 0, lbl_804D8054->fbWidth, lbl_804D8054->efbHeight);
    GXSetDispCopyDst(lbl_804D8054->fbWidth, lbl_804D8054->efbHeight);
    GXSetDispCopyYScale((f32)lbl_804D8054->xfbHeight / (f32)lbl_804D8054->efbHeight);
    GXSetCopyFilter(lbl_804D8054->aa, lbl_804D8054->sample_pattern, GX_TRUE, lbl_804D8054->vfilter);
    GXSetCopyClamp((GXFBClamp)(GX_CLAMP_TOP | GX_CLAMP_BOTTOM));
    GXSetDispCopyGamma(GX_GM_1_0);
    if (lbl_804D8054->aa) {
        GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
        GXSetDither(GX_FALSE);
    }
    else {
        GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
        GXSetDither(GX_TRUE);
    }
}

void fn_80007788() {
    VIConfigure(lbl_804D8054);
    fn_8000766C();
    GXCopyDisp(lbl_804D8044, GX_TRUE);
    GXCopyDisp(lbl_804D8044, GX_TRUE);
    GXFlush();
    GXDrawDone();
    VIFlush();
    VIWaitForRetrace();
    VIWaitForRetrace();
}

void fn_800077DC() {
    fn_80007398(&lbl_804D8038);
}

void fn_80007800() {
    GXInvalidateTexAll();
    GXInvalidateVtxCache();
    GXSetScissor(0, 0, lbl_804D8054->fbWidth, lbl_804D8054->xfbHeight);
}

void fn_8000783C() {
    GXDrawDone();
    OSReceiveMessage(&lbl_803A3600.mMessageQueue, nullptr, OS_MESSAGE_BLOCK);
    lbl_803A3600._0 = VIGetRetraceCount();
    VIWaitForRetrace();
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);

    if (lbl_804D8044 != nullptr) {
        GXCopyDisp(lbl_804D8044, GX_TRUE);
    }

    if ((lbl_804D8038._0 & 1)) {
        VISetBlack(GX_FALSE);
    }
    else {
        VISetBlack(GX_TRUE);
    }

    VISetNextFrameBuffer(lbl_804D8044);
    VIFlush();

    if (lbl_804D8038._2) {
        lbl_804D8038._3 ^= 1;
        lbl_804D8044 = lbl_804D804C[lbl_804D8038._3];
    }

    GXFlush();
}

void fn_80007910() {
  fn_8000766C();
  if (lbl_804D8038._2 == true) {
    GXDrawDone();
    GXSetColorUpdate('\x01');
    GXSetAlphaUpdate('\x01');
    GXCopyDisp(lbl_804D8044, '\x01');
    GXFlush();
    fn_800075EC(&lbl_804D8038);
    OSReceiveMessage(&lbl_803A3600.mMessageQueue, NULL, OS_MESSAGE_BLOCK);
    lbl_803A3600._0 = VIGetRetraceCount();
  } else {
    fn_8000783C();
  }
  void* frameBuf = lbl_804D8044;

  JUTDirectPrint::getManager()->changeFrameBuffer(frameBuf, 640, 480);
}

void fn_800079B0() {
    if (lbl_804D8054 != lbl_804CFF70[lbl_804D8034]) {
        lbl_804D8054 = lbl_804CFF70[lbl_804D8034];
        VIConfigure(lbl_804D8054);
        fn_8000766C();
        GXCopyDisp(lbl_804D8044, GX_TRUE);
        GXCopyDisp(lbl_804D8044, GX_TRUE);
        GXFlush();
        GXDrawDone();
        VIFlush();
        VIWaitForRetrace();
        VIWaitForRetrace();
    }
}

void fn_80007A24() {
    GXSetScissor(0, 0, lbl_804D8054->fbWidth, lbl_804D8054->xfbHeight);
    GXSetViewportJitter(0.0f, 0.0f, lbl_804D8054->fbWidth, lbl_804D8054->xfbHeight, 0.0f, 1.875f, 1);
    Mtx orthoMtx;
    MTXOrtho(orthoMtx, -0.0f, 3.96875f, -0.0f, lbl_804D8054->fbWidth, -1.875f, 4.4765625f);
    GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);
    GXSetCullMode(GX_CULL_NONE);
    GXLoadPosMtxImm(lbl_8021DA4C, 0);
    GXLoadNrmMtxImm(lbl_8021DA4C, 0);
    GXLoadTexMtxImm(lbl_8021DA4C, 0x3c, GX_MTX2x4);
    GXSetCurrentMtx(0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_RGBA4, '\0');
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, '\0');
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_RGBX8, '\x0f');
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_CLR_RGBA, GX_RGBX8, '\x0f');
    GXSetNumChans('\x01');
    GXSetChanCtrl(GX_COLOR0A0, '\0', GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, '\0', GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
}
