#ifndef SCENE_H
#define SCENE_H

#include <types.h>

#define MAX_SCENE_NAME_SIZE 16

typedef void (*SceneInitFunc)();
typedef u32 (*SceneUpdateFunc)();
typedef void (*SceneDrawFunc)();
typedef void (*SceneDestroyFunc)();

enum Scene_ID {
    SCENE_BOOT,
    SCENE_TITLE,
    SCENE_MAIN_GAME,
    SCENE_SELECT,
    SCENE_OPENING,
    SCENE_STUFF_ROLL,
    SCENE_ENDING,
    SCENE_MOVIE,
    SCENE_MAX,
};

struct Scene {
    /* 0x00 */ char mName[MAX_SCENE_NAME_SIZE];
    /* 0x10 */ s16 _10;
    /* 0x14 */ SceneInitFunc mInitFn;
    /* 0x18 */ SceneUpdateFunc mUpdateFn;
    /* 0x1C */ SceneDrawFunc mDrawFn;
    /* 0x20 */ SceneDestroyFunc mDestroyFn;
};

extern Scene* sCurScene;
extern u32 sCurSceneIdx;
extern Scene* sSceneTable[SCENE_MAX];

#endif
