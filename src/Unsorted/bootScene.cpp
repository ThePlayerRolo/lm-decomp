#include "Unsorted/bootScene.hpp"
#include "JSystem/J2D/J2DOrthoGraph.hpp"
#include "Unsorted/80007018.hpp"
#include "Unsorted/LMDisplayUtil.hpp"
#include "Unsorted/staticDataAramData.h"
#include "Unsorted/80005EB8.hpp"
#include "Unsorted/LMDvdFile.hpp"
#include "Unsorted/80008418.hpp"
#include <JSystem/JKernel/JKRExpHeap.hpp>
#include "JSystem/JKernel/JKRMemArchive.hpp"
#include "JSystem/J2D/J2DPicture.hpp"

//.data
static f32 dummy_float_data[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.95f, 0.9f, 0.85f, 1.0f, 0.9f, 0.75f, 0.3f, 0.0f, 0.0f};

//NOTE: Files are created during setup
#if VERSION == VERSION_USA
#include "staticdata_usa_arc.inc"
#define STATIC_DATA staticdata_usa_arc
#else
#include "staticdata_arc.inc"
#define STATIC_DATA  staticdata_arc
#endif

s32 lbl_802FB380[3872] = { };



// externs
extern void fn_80066FAC(JKRMemArchive*);
extern void fn_80188594(void*, u32, u32);
extern void fn_8004D4C8();
extern void fn_80188714(void*);
extern void fn_80188638();
extern bool fn_80188740();
extern void fn_80009490();
extern void fn_8005FD80();
extern void fn_8003EB44();
extern void fn_80009B80();
extern void fn_8000A40C(f32, f32, f32, f32, f32, f32, Mtx, s32, s32, u32);
extern GXColor lbl_804CFF88;
extern s32 lbl_804D8098;
extern s32 lbl_804D809C;

GXColor lbl_804CFFB0 = { 255, 255, 255, 32 };

namespace BootScene {

    Scene sScene = {
        "BOOT",
        1,
        init,
        update,
        draw,
        destroy
    };

    // needs to be here for position
    const char* ninLogoFileName = "/ninlogo.pcm";

    s32 lbl_804D8110;
    BootSceneState sCurBootSceneState;
    u16 lbl_804D8118;
    f32 lbl_804D811C;
    J2DPicture* sNintendoLogoPicture;
    JKRMemArchive* sStaticDataArchive;

    static void dvdFileOpenCallback(void* param_1, LMDvdFileInfo* param_2) {
        void* block = JKRAllocFromHeap(nullptr, param_2->_64->size(), 32);
        param_2->_64->fn_800071D0((LMDvdFileInfoBlock*)block);
        fn_80006138(param_2->_64);
        fn_80066FAC(new JKRMemArchive(block, 0, MBF_0));
    }

    void loadStaticDataArchives() {
        fn_800061B8(16);
        fn_80006204();
        void* game_usaData = LMDvdFileOpen("/Game/game_usa.szp", dvdFileOpenCallback, 0, 0);
        lbl_804D8014->becomeCurrentHeap();
        fn_800061B8(3);
        u8* data = (u8*)sStaticDataArchive->getResource("/res_titl.szp");

        sResTitleAramData.setAddrAndSize(JKRMainRamToAram(data, (JKRAramBlock*)nullptr,
            sStaticDataArchive->getResSize(data), EXPAND_SWITCH_DEFAULT, 0, nullptr, -1));

        data = (u8*)sStaticDataArchive->getResource("/gameboy.szp");

        sGameboyAramData.setAddrAndSize(JKRMainRamToAram(data, (JKRAramBlock*)nullptr,
            sStaticDataArchive->getResSize(data), EXPAND_SWITCH_DEFAULT, 0, nullptr, -1));

        data = (u8*)sStaticDataArchive->getResource("/guidemap.szp");

        sGuidemapAramData.setAddrAndSize(JKRMainRamToAram(data, (JKRAramBlock*)nullptr,
            sStaticDataArchive->getResSize(data), EXPAND_SWITCH_DEFAULT, 0, nullptr, -1));

        data = (u8*)sStaticDataArchive->getResource("/res_paus.szp");

        sResPauseAramData.setAddrAndSize(JKRMainRamToAram(data, (JKRAramBlock*)nullptr,
            sStaticDataArchive->getResSize(data), EXPAND_SWITCH_DEFAULT, 0, nullptr, -1));

        data = (u8*)sStaticDataArchive->getResource("/res_list.szp");

        sResListAramData.setAddrAndSize(JKRMainRamToAram(data, (JKRAramBlock*)nullptr,
            sStaticDataArchive->getResSize(data), EXPAND_SWITCH_DEFAULT, 0, nullptr, -1));

        u8 bVar1 = true;
        do {
            bVar1 = LMDvdFile::checkCurUnk0();
        } while(bVar1 != 0);
    }

    void loadStaticData() {
        lbl_804D8014->changeGroupID(4);
        fn_80188594(JKRAllocFromHeap(lbl_804D8014, 0xC0000, 0x20), 0xC0000, 0xF00000);
        fn_8004D4C8();
        fn_80188714(sStaticDataArchive->getResource("/ninlogo.pcm"));
        loadStaticDataArchives();
        fn_80188638();
        do { } while(fn_80188740() == true);
    }

    // problems but can't create a scratch because tu is too big lol
    void init() {
        sCurBootSceneState = STATE_0;
        lbl_804D8110 = 0;
        lbl_804D8014->becomeCurrentHeap();
        fn_80009490();
        fn_8005FD80();
        fn_800061B8(8);
        fn_8003EB44();
        fn_800061B8(26);
        lbl_804D8118 = 0;
        lbl_804D811C = 0.0f;
        lbl_804CFFB0.a = 32; // why?????

        sStaticDataArchive = new JKRMemArchive(STATIC_DATA, 0, MBF_0);

        LMDvdFileInfoBlock* nintendoSzpBlock = (LMDvdFileInfoBlock*)sStaticDataArchive->getResource("/nintendo.szp");
        u32 size = nintendoSzpBlock->size();
        fn_80006204();
        JUTTexture* data = (JUTTexture*)fn_80006080(size, 0x20);
        lbl_804D8014->becomeCurrentHeap();
        nintendoSzpBlock->fn_800071D0((LMDvdFileInfoBlock*)data);
        sNintendoLogoPicture = new J2DPicture(data);
    }

    void destroy() {
        delete sNintendoLogoPicture;
        sStaticDataArchive->unmount();
        fn_80006204();
    }


    u32 update() {
        u32 ret;
        switch (sCurBootSceneState) {
        case STATE_0:
            fn_80007040(loadStaticData);
            fn_80007F28();
            sCurBootSceneState = STATE_1;
            return 0;
        case STATE_1:
            if (fn_80007090() == 0) {
                return 0;
            }
            lbl_804D8110 = 1;
            sCurBootSceneState = STATE_2;
            return 0;
            break;
        default:
            return 1;
        }
    }

    // problems but can't create a scratch because tu is too big lol
    void draw() {
        STACK_PAD_VAR(4);
        static s32 lbl_804D8128;
        static s8 isNotFirstDraw;

        if (!isNotFirstDraw) {
            lbl_804D8128 = 0;
            isNotFirstDraw = true;
        }
        fn_80009B80();
        fn_80008654(&lbl_803A3820);
        GXSetChanMatColor(GX_COLOR0A0, lbl_804CFFB0);
        LMSetViewportJitter(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
        GXSetScissor(0, 0, 640, 480);
        GXSetCurrentMtx(0);
        GXSetNumChans(1);
        GXSetNumTevStages(1);
        Mtx mtx;
        fn_8000A40C(0.2f, 0.2f, 0.2f, 0.0f, 0.0f, 0.0f, mtx, 0, 0, lbl_804D8118);
        PSMTXConcat(lbl_803A3820._18C, mtx, mtx);
        GXLoadNrmMtxImm(mtx, 0);
        fn_8000A40C(0.2f, 0.2f, 0.2f, 0.0f, 0.0f, lbl_804D811C, mtx, 0, 0, lbl_804D8118);
        PSMTXConcat(lbl_803A3820._18C, mtx, mtx);
        GXLoadNrmMtxImm(mtx, 0);
        J2DOrthoGraph graph(0, 0, 640, 480);
        graph.setPort();
        GXColor color = (GXColor){ 220, 0, 0, 255};
        sNintendoLogoPicture->mBlack = lbl_804CFF88;
        sNintendoLogoPicture->mWhite = color;
        sNintendoLogoPicture->draw(0, 0, 640, 480, false, false, false);
        if (lbl_804D809C <= lbl_804D8098) {
            fn_80007E50(1);
        }
        if (sCurBootSceneState == STATE_2) {
            lbl_804D8128++;
        }
    }
};

u8* getStaticDataArr() {
    return STATIC_DATA;
}
