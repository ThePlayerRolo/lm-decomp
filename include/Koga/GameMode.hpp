#ifndef GAME_MODE_H_
#define GAME_MODE_H_

#include "types.h"

namespace Koga {
    class GameMode;

    struct GameModeBase {
        // Set by fn_800B9D1C, destroyed by fn_800B9DD0 during exit to title screen
        static GameMode* sCurrentGameMode;
        // 0 at title screen, 1 when actually playing
        static int sGameModeCount;

        GameModeBase();
        inline ~GameModeBase() { sGameModeCount -= 1; }

        static void incrementGameModeCount();
    };

    class GameMode : private GameModeBase {
    public:
        GameMode();
        ~GameMode();

        // This looks like a destroy() function or something?
        // It does destructor-like things when overridden in Koga::MissionMode.
        /* 0x08 */ virtual void vt_8() = 0;

        /* 0x0C */ virtual void vt_C();
        /* 0x10 */ virtual void vt_10();
        /* 0x14 */ virtual void vt_14();
        /* 0x18 */ virtual void vt_18();
    };
}

#endif
