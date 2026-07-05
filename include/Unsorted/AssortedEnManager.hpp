#ifndef ASSORTED_EN_MANAGER_HPP
#define ASSORTED_EN_MANAGER_HPP

#include "Koga/ToolData.hpp"
#include <JSystem/JGeometry/JGVec3.hpp>

class unkEnCharacter;
class unkEnManager1;
class MoveObj;

namespace Koga {
    class ToolData;
}

void* fn_800AD39C(long); //Probably a player object, unsure
void fn_80068EF8();
void fn_800BF8B8(unkEnCharacter*, Koga::ToolData*, int);
u32 fn_80017ADC(JGeometry::TVec3f, int);
void* fn_800C19CC(void*, s32);
char fn_800C15E0(unkEnCharacter*);
void fn_800C17EC(unkEnCharacter*);
void fn_80067CB0(void*, f32, f32, f32);
void fn_800BF81C(unkEnCharacter*);
void* fn_800E9F90(unkEnManager1*);

#endif
