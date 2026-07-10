#ifndef BOOT_SCENE_H
#define BOOT_SCENE_H

#include "Unsorted/Scene.hpp"
#include <version.h>

class JKRMemArchive;
class J2DPicture;

namespace BootScene {
    enum BootSceneState {
        STATE_0,
        STATE_1,
        STATE_2,
    };
    
    extern s32 lbl_804D8110;
    extern BootSceneState sCurBootSceneState;
    extern u16 lbl_804D8118;
    extern f32 lbl_804D811C;
    extern J2DPicture* sNintendoLogoPicture;
    extern JKRMemArchive* sStaticDataArchive;

    void init();
    void destroy();
    u32 update();
    void draw();

    extern Scene sScene;
}

u8* getStaticDataArr();


#endif
