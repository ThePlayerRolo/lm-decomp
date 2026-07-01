#include "Koga/MissionMode.hpp"
#include "Koga/MapCol.hpp"
#include "Koga/EnTypesManager.hpp"
#include "Koga/EnManager.hpp"
#include "Koga/EnemyGenManager.hpp"
#include "Koga/JmpMessage.hpp"
#include "Koga/CharacterColManager.hpp"
#include "Koga/SimpleModeler.hpp"
#include "Koga/ToolData.hpp"

#include "Unsorted/LMDvdFile.hpp"
#include <JSystem/JKernel/JKRFileFinder.hpp>
#include <JSystem/JKernel/JKRArchive.hpp>
#include <stdio.h>

dummy_float_data()

//TODO: Remove these
extern int sCurMapNo;

namespace Koga {

    MissionMode::MissionMode()
        : GameMode()
        , mEnTypesMgr(nullptr)
        , mEnMgr(nullptr)
        , mEnGenMgr(nullptr)
        , mMapData(nullptr)
        , mJmpCount(0)
        , mMapArchive(nullptr)
        , mCharColMgr(nullptr)
        , mJmpMsgSender(nullptr)
    {
        MapCol::newMapCol();
        EnTypesManager::newManager();
        mEnTypesMgr = EnTypesManager::getManager();
        mEnMgr = new EnManager();
        mCharColMgr = new CharacterColManager();
        mJmpMsgSender = new JmpMessageSender();
        mEnGenMgr = new EnemyGenManager();
        SimpleModeler::newSimpleModeler();

        init();
    }

    inline Koga::MissionMode::~MissionMode() {
        mMapArchive->unmount();
        SimpleModeler::getCurSimpleModeler()->deleteSimpleModeler();
        delete mEnGenMgr;
        delete mJmpMsgSender;
        delete mCharColMgr;
        delete[] mMapData;
        delete mEnMgr;
        EnTypesManager::deleteManager();
        MapCol::deleteMapCol();
        sMissionMode = 0;
    }

    //https://decomp.me/scratch/2xA8s
    void Koga::MissionMode::vt_8(s16) {
        delete this;
    }

    MissionMode* Koga::MissionMode::create() {
        // If we are on the TitleScreen
        if (Koga::GameModeBase::getGameModeCount() == 0)
            sMissionMode = new Koga::MissionMode();
        return sMissionMode;
    }

    //Needed for data ordering
    void unk() {
        char data[10];
        sprintf(data, "/Map/map");
    }

    void MissionMode::init() {
        char mapName[128];

        sprintf(mapName, "%s%d.szp", "/Map/map", sCurMapNo);
        mMapArchive = (JKRArchive*)fn_80006930(mapName, nullptr);

        mEnMgr->loadCharacterInfo(mMapArchive);
        s32 jmpFileCount = mMapArchive->countFile("/jmp") - 2;

        if (jmpFileCount > 0) {
            mJmpCount = jmpFileCount;
            mMapData = new ToolData[jmpFileCount];

            JKRFileFinder* jmpFile = mMapArchive->getFirstFile("/jmp");
            for (int i = 0; i < jmpFileCount; i++, jmpFile->findNextFile()) {
                //Why the space lol
                mMapData[i].attach((ToolData::JMapData*)mMapArchive->getResource('JMP ', jmpFile->mBase.mFileName));
            }
            delete jmpFile;
        }
        mJmpMsgSender->add(getJmpResource("ObjInfo"));
        mJmpMsgSender->add(getJmpResource("CharacterInfo"));
        mJmpMsgSender->add(getJmpResource("KeyInfo"));
        mJmpMsgSender->add(getJmpResource("GeneratorInfo"));
        mJmpMsgSender->add(getJmpResource("EnemyInfo"));
        mJmpMsgSender->add(getJmpResource("ObserverInfo"));

        mJmpMsgSender->addReceiver(mEnMgr);
    }

    void MissionMode::vt_10() {
        loadCollisionInfo("/col.mp", "/jmp/PolygonInfo");
        EnTypesManager::getManager()->loadParameters();
        mJmpMsgSender->addReceiver(mEnGenMgr);
    }

    void MissionMode::loadCollisionInfo(const char* pFile, const char* pPath) {
        MapCol* curColl = MapCol::getCurMapCol();

        curColl->load(mMapArchive->getResource(pFile), mMapArchive->getResource(pPath));
    }

    // Toggles the loaded JMP tables between their blackout mode variants
    void MissionMode::toggleBlackoutTables(Mission mission) {
        switch (mission) {
        case MISSION_DEFAULT:
            mJmpMsgSender->remove(getJmpResource("TeidenEnemyInfo"));
            mJmpMsgSender->remove(getJmpResource("TeidenCharacterInfo"));
            mJmpMsgSender->remove(getJmpResource("TeidenObserverInfo"));
            mJmpMsgSender->remove(getJmpResource("TeidenKeyInfo"));

            mJmpMsgSender->add(getJmpResource("EnemyInfo"));
            mJmpMsgSender->add(getJmpResource("CharacterInfo"));
            mJmpMsgSender->add(getJmpResource("ObserverInfo"));
            mJmpMsgSender->add(getJmpResource("KeyInfo"));
            break;
        case MISSION_BLACKOUT:
            mJmpMsgSender->remove(getJmpResource("EnemyInfo"));
            mJmpMsgSender->remove(getJmpResource("CharacterInfo"));
            mJmpMsgSender->remove(getJmpResource("ObserverInfo"));
            mJmpMsgSender->remove(getJmpResource("KeyInfo"));

            mJmpMsgSender->add(getJmpResource("TeidenEnemyInfo"));
            mJmpMsgSender->add(getJmpResource("TeidenCharacterInfo"));
            mJmpMsgSender->add(getJmpResource("TeidenObserverInfo"));
            mJmpMsgSender->add(getJmpResource("TeidenKeyInfo"));
            break;
        }
        mJmpMsgSender->vt_10();
    }

    void MissionMode::addJmpReceiver(void* pReceiver) {
        mJmpMsgSender->addReceiver(pReceiver);
    }

    void* MissionMode::getMapArchiveResource(const char* name, u32 type) {
        return mMapArchive->getResource(type, name);
    }


    //https://decomp.me/scratch/FshSz
    ToolData* MissionMode::getJmpResource(const char* pName) {
        ToolData jmpToolData;
        jmpToolData.attach((ToolData::JMapData*)mMapArchive->getResource('JMP ', pName));
        ToolData* mapData = &mMapData[0];

        for (; mapData != &mMapData[mJmpCount] && mapData->getJMapData() != jmpToolData.getJMapData(); mapData++) {}

        if (mapData == &mMapData[mJmpCount] || mapData->getJMapData() == nullptr)
            return nullptr;

        return mapData;
    }

    void MissionMode::vt_14() {
        mEnMgr->fn_800E5AE8();
        mJmpMsgSender->vt_0C();
        mEnGenMgr->fn_800C2F44();
        MapCol::getCurMapCol()->fn_800BC898();
    }

    void MissionMode::vt_18() {
        SimpleModeler::getCurSimpleModeler()->draw();
    }
}
