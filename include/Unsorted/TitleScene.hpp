#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "Unsorted/Scene.hpp"

class JKRMemArchive;
class J2DPicture;

namespace TitleScene {
    void init();
    void destroy();
    u32 update();
    void draw();

    extern Scene sScene;
}


#endif
