#ifndef EN_TYPES_MANAGER_H_
#define EN_TYPES_MANAGER_H_

#include <types.h>
#include <JSystem/JORReflexible.hpp>

class ToolDataRef;
class unkEnCharacter;

namespace Koga {
    class EnTypesManager : public JORReflexible {
    public:
        EnTypesManager();
        /* 0x08 */ virtual ~EnTypesManager();

        static void newManager();
        static void deleteManager();
        static EnTypesManager* getManager() { return sManager; }

        void loadParameters();
    public:
        /* 0x04 */  s32** _4;  //TODO: This is an array of TParams

        static EnTypesManager* sManager;
    };

};

// All of these are referenced in EnManager. No arg types or return types are guaranteed.
s32 fn_800DAB18(char*);
s32 fn_800DABA4(ToolDataRef);
s32 fn_800DAC84(s32);
void* fn_800DAD00(void*);
unkEnCharacter* fn_800DB034(void*);
void* fn_800DB06C(int);

#endif
