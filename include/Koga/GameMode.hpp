#ifndef GAME_MODE_H_
#define GAME_MODE_H_

#include "types.h"
#include "JSystem/JORReflexible.hpp"

namespace Koga {
    struct GameModeBase {
        // 0 at title screen, 1 when actually playing.
        static int sGameModeCount;

        GameModeBase();
        ~GameModeBase() { sGameModeCount -= 1; }

        static void incrementGameModeCount();
    };

    class GameMode : private GameModeBase {
    public:
        GameMode();
        ~GameMode();

        /* 0x08 */ virtual void vt_8() = 0;
        /* 0x0C */ virtual void vt_C();
        /* 0x10 */ virtual void vt_10();
        /* 0x14 */ virtual void vt_14();
        /* 0x18 */ virtual void vt_18();
    };
}

#endif
