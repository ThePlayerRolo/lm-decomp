#ifndef EN_MANAGER_H_
#define EN_MANAGER_H_

#include "types.h"
#include <JSystem/JORReflexible.hpp>

class JKRArchive;

namespace Koga {
    class EnManager : public JORReflexible {
    public:
        EnManager();
        /* 0x08 */ virtual ~EnManager();
        /* 0x0C */ virtual void vt_C();
        /* 0x10 */ virtual void vt_10();
        /* 0x14 */ virtual void vt_14();

        void load(JKRArchive* archive);
        void fn_800E5AE8();
        void fn_800E46C0();

    public:
        /* 0x04 */  u8 _4[0xE44]; //For matching size, will replace later
    };

};

#endif
