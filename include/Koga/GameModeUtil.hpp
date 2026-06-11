#ifndef GAMEMODE_UTIL_H_
#define GAMEMODE_UTIL_H_

#include "Koga/MissionMode.hpp"

class JKRArchive;

namespace Koga {
    class ToolData;

    namespace GameModeUtil {
        void curGameModeCreate();
        void fn_800B9D40();
        void fn_800B9D70();
        void curGameModeDraw();
        void curGameModeDestroy();
        void fn_800B9E0C();
        void fn_800B9E34();
        void fn_800B9E5C();
        void toggleBlackoutTables(MissionMode::Mission mission);
        void fn_800B9EBC();
        void fn_800B9ED0();
        void* getPathResource(const char* pName);
        void addJmpReceiver(void* pReceiver);
        JKRArchive* getMapArchive();
        ToolData* getMapSection(const char* pName);
    };
}

#endif
