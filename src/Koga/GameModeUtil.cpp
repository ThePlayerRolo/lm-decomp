#include "Koga/GameModeUtil.hpp"
#include "Koga/EnManager.hpp"
#include "Koga/EnemyGenManager.hpp"
#include "Koga/JmpMessage.hpp"
#include "Koga/MissionMode.hpp"

namespace Koga { namespace GameModeUtil {

    void curGameModeCreate() {
        GameModeBase::sCurrentGameMode = MissionMode::create();
    }

    void fn_800B9D40() {
        GameModeBase::sCurrentGameMode->vt_10();
    }

    void fn_800B9D70() {
        GameModeBase::sCurrentGameMode->vt_14();
    }

    void curGameModeDraw() {
        GameModeBase::sCurrentGameMode->vt_18();
    }

    void curGameModeDestroy() {
        //TODO: A delete is definitely used here however vt_8 is confusing

        //delete GameModeBase::sCurrentGameMode;

        if (GameModeBase::sCurrentGameMode != nullptr) {
            GameModeBase::sCurrentGameMode->vt_8(1);
        }
    }

    void fn_800B9E0C() {
        MissionMode* missionMode = MissionMode::getMissionMode();

        missionMode->getEnManager()->fn_800E46C0();
    }

    void fn_800B9E34() {
        MissionMode* missionMode = MissionMode::getMissionMode();

        missionMode->getJmpMsgSender()->fn_800EAB1C();
    }

    void fn_800B9E5C() {
        MissionMode* missionMode = MissionMode::getMissionMode();

        missionMode->getJmpMsgSender()->vt_10();
    }

    void toggleBlackoutTables(MissionMode::Mission mission) {
        MissionMode* missionMode = MissionMode::getMissionMode();

        missionMode->toggleBlackoutTables(mission);
    }

    void fn_800B9EBC() {
        MissionMode* missionMode = MissionMode::getMissionMode();

        missionMode->getEnemyGenManager()->setUnk8(false);
    }

    void fn_800B9ED0() {
        MissionMode* missionMode = MissionMode::getMissionMode();

        missionMode->getEnemyGenManager()->setUnk8(true);
    }

    void* getPathResource(const char* pName) {
        MissionMode* missionMode = MissionMode::getMissionMode();

        return missionMode->getMapArchiveResource(pName, 'PATH');
    }

    void addJmpReceiver(void* pReceiver) {
        MissionMode* missionMode = MissionMode::getMissionMode();

        missionMode->addJmpReceiver(pReceiver);
    }

    JKRArchive* getMapArchive() {
        return MissionMode::getMissionMode()->getMapArchive();
    }

    ToolData* getMapSection(const char* pName) {
        MissionMode* missionMode = MissionMode::getMissionMode();

        return missionMode->getMapSectionData(pName);
    }
}
}
