#ifndef EN_TYPES_MANAGER_H_
#define EN_TYPES_MANAGER_H_

#include <types.h>
#include <JSystem/JORReflexible.hpp>

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

#endif
