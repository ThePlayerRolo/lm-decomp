#ifndef MISSION_MODE_H_
#define MISSION_MODE_H_

#include "JSystem/JORReflexible.hpp"
#include "Koga/GameMode.hpp"

class CharacterColManager;
class JmpMessageSender;
class JKRArchive;

namespace Koga {
    class EnTypesManager;
    class EnManager;
    class EnemyGenManager;
    class ToolData;

    class MissionMode : public GameMode, public JORReflexible {
    public:
        /* TODO: Maybe change the name? */
        enum Mission {
            MISSION_BLACKOUT,
            MISSION_DEFAULT,
        };

        MissionMode();
        ~MissionMode();

        /* 0x08 */ virtual void vt_8(s16);

        /* 0x0C */ virtual void init();
        /* 0x10 */ virtual void vt_10();
        /* 0x14 */ virtual void vt_14();
        /* 0x18 */ virtual void vt_18();

        static MissionMode* create();
        static inline MissionMode* getMissionMode() { return sMissionMode; }

        void loadCollisionInfo(const char* pFile, const char* pPath);
        void toggleBlackoutTables(Mission mission);
        void addJmpReceiver(void* pReceiver);
        void* getMapArchiveResource(const char* name, u32 type);

        ToolData* getMapSectionData(const char* pName);

        inline EnManager* getEnManager() { return mEnMgr; }
        inline EnemyGenManager* getEnemyGenManager() { return mEnGenMgr; }
        inline JKRArchive* getMapArchive() { return mMapArchive; }
        inline JmpMessageSender* getJmpMsgSender() { return mJmpMsgSender; }

    public:
        /* 0x04 */ EnTypesManager* mEnTypesMgr;
        /* 0x08 */ EnManager* mEnMgr;
        /* 0x0C */ EnemyGenManager* mEnGenMgr;
        /* 0x10 */ ToolData* mMapData;
        /* 0x14 */ s32 mJmpCount;
        /* 0x18 */ JKRArchive* mMapArchive;
        /* 0x1C */ CharacterColManager* mCharColMgr;
        /* 0x20 */ JmpMessageSender* mJmpMsgSender;

        static MissionMode* sMissionMode;
    };
}

#endif
