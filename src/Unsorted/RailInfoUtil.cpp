#include "Unsorted/RailInfoUtil.hpp"
#include "Koga/GameModeUtil.hpp"
#include "Koga/ToolData.hpp"

//Mostly matches minus stack size
int getLadderCount() {
    Koga::ToolData* railInfo = Koga::GameModeUtil::getJmpResource("RailInfo");

    int ladderCount = 0;
    if (railInfo != nullptr) {
        for (int i = 0; i < railInfo->getDataEntryNum(); i++) {
            u32 useVal = -1;
            railInfo->getValue(i, "use", &useVal);

            if (useVal == 1) {
                ladderCount++;
            }
        }
    }

    return ladderCount;
}

const char* getLadderName(int ladderIndex) {
    Koga::ToolData* railInfo = Koga::GameModeUtil::getJmpResource("RailInfo");
    const char* ladderName = nullptr;

    for (int i = 0, entryIndex = 0; i < railInfo->getDataEntryNum(); i++, entryIndex++) {
        u32 useVal = -1;
        railInfo->getValue(i, "use", &useVal);

        if (useVal == 1) {
            if (entryIndex == ladderIndex) {
                railInfo->getValue(i, "name", &ladderName);
                return ladderName;
            }
        }
    }
  
  return ladderName;
}

// Some mismatches due to the operator new for Koga::ToolData vs just calling the constructor, not sure why/how here
// https://decomp.me/scratch/d7vM7
int getLadderPathEntryCount(int ladderIndex) {
    Koga::ToolData* railInfo = Koga::GameModeUtil::getJmpResource("RailInfo");
    const char* ladderName = nullptr;
    u32 ladderCount = 0;

    for (int i = 0, entryIndex = 0; i < railInfo->getDataEntryNum(); i++, entryIndex++) {
        u32 useVal = -1;
        railInfo->getValue(i, "use", &useVal);

        if (useVal == 1) {
            if (entryIndex == ladderIndex) {
                railInfo->getValue(i, "name", &ladderName);
                Koga::ToolData::JMapData* ladderPath = reinterpret_cast<Koga::ToolData::JMapData*>(Koga::GameModeUtil::getPathResource(ladderName));
                if (ladderPath != nullptr) {
                    Koga::ToolData* ladderData = new Koga::ToolData();
                    ladderData->attach(ladderPath);
                    ladderCount = ladderData->getDataEntryNum();
                    return ladderCount;
                }
            }
        }
    }
  
  return ladderCount;
}

// Similar to getLadderPathEntryCount, mismatch due to operator new.
// https://decomp.me/scratch/vVvhu
bool getLadderPositionByIndex(JGeometry::TVec3f* out, int ladderIndex, u32 entryIndex) {
    const char* pathName = getLadderName(ladderIndex);
    s32 maxIndex = -1;

    Koga::ToolData::JMapData* ladderPath = reinterpret_cast<Koga::ToolData::JMapData*>(Koga::GameModeUtil::getPathResource(pathName));
    if (ladderPath != nullptr) {
        Koga::ToolData* ladderData = new Koga::ToolData();
        ladderData->attach(ladderPath);
        maxIndex = ladderData->getDataEntryNum();
    }

    bool ladderPosFound = false;
    if (entryIndex < maxIndex) {
        Koga::ToolData* railInfo = Koga::GameModeUtil::getJmpResource("RailInfo");
        const char* ladderName = nullptr;
        for (int i = 0, entryIndex = 0; i < railInfo->getDataEntryNum(); i++, entryIndex++) {
            u32 useVal = -1;
            railInfo->getValue(i, "use", &useVal);

            if (useVal == 1) {
                if (entryIndex == ladderIndex) {
                    railInfo->getValue(i, "name", &ladderName);
                    break;
                }
            }
        }

        ladderPath = reinterpret_cast<Koga::ToolData::JMapData*>(Koga::GameModeUtil::getPathResource(ladderName));
        if (ladderPath != nullptr) {
            Koga::ToolData* ladderData = new Koga::ToolData();
            ladderData->attach(ladderPath);
            ladderData->getValue(entryIndex, "pnt0_x", &out->x);
            ladderData->getValue(entryIndex, "pnt0_y", &out->y);
            ladderData->getValue(entryIndex, "pnt0_z", &out->z);
            ladderPosFound = true;
        }
    }

    return ladderPosFound;
}
