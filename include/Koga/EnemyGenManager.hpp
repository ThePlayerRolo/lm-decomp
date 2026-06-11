#ifndef ENEMY_GEN_MANAGER_H_
#define ENEMY_GEN_MANAGER_H_

#include "types.h"
#include <JSystem/JORReflexible.hpp>

namespace Koga {
    class EnemyGenManager : public JORReflexible {
    public:
        EnemyGenManager();
        /* 0x08 */ virtual ~EnemyGenManager();
        /* 0x0C */ virtual void vt_C();
        /* 0x10 */ virtual void vt_10();
        /* 0x14 */ virtual void vt_14();

        void fn_800C2F44();

        inline void setUnk8(bool val) { _8 = val; }
    public:
        /* 0x4 */  s32** _4; //An array, probably of Enemies
        /* 0x8 */ bool _8;
    };

};

#endif
