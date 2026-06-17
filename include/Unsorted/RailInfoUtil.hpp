#ifndef RAILINFOUTIL_H_
#define RAILINFOUTIL_H_

#include "types.h"
#include <JSystem/JGeometry/JGVec3.hpp>

int getLadderCount();
const char* getLadderName(int);

// Unsure about these middle ones, just quick glances
// fn_80092608() through fn_80092F60() not reviewed.
void fn_80093000(); // some ladder length thing?
void fn_800930E8(); // some ladder cross product?
void fn_80093220(); // some ladder add/scale function?

int getLadderPathEntryCount(int); //TODO better name
bool getLadderPositionByIndex(JGeometry::TVec3f*, int, u32); //TODO better name

#endif
