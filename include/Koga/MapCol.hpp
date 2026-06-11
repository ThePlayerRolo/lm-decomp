#ifndef MAP_COLL_H_
#define MAP_COLL_H_

#include "types.h"
#include <JSystem/JORReflexible.hpp>
#include <JSystem/JGeometry/JGVec3.hpp>

namespace Koga {
    class ToolData;

    class MapCol : public JORReflexible {
    public:

        //TODO: Verify this since its confusing
        //The members function both as a int/short, and Vector
        struct unkSubStruct {
            JGeometry::TVec3f _0[5];
        };

        MapCol() : _4(nullptr), _8(0x8000), _C(-1), _10(-1) { }
        /* 0x08 */ virtual ~MapCol();

        static void newMapCol();
        static void deleteMapCol();
        static MapCol* getCurMapCol() { return sCurMapCol; }

        void load(void*, void*);

        JGeometry::TVec3f* fn_800BBBE0(JGeometry::TVec3f*);
        bool fn_800BBCA8(JGeometry::TVec3f*,  JGeometry::TVec3f&);
        s32* fn_800BBD54(JGeometry::TVec3f&);
        void fn_800BC898(); // Is stubbed out
        void fn_800BC89C(s32);
        void fn_800BC8B4(s32);
        int fn_800BC8CC(s16);
        f32 fn_800BBE2C(JGeometry::TVec3f&);
        ToolData* getPolygonInfo();

        inline bool vecCheckto_4(JGeometry::TVec3f& param_1) {
            if (param_1.x < 0.0f || _4->_0[2].x <= param_1.x || param_1.y < 0.0f || _4->_0[2].y <= param_1.y || param_1.z < 0.0f || _4->_0[2].z <= param_1.z)
            {
                return false;
            }
            return true;
        }

    public:
        /* 0x04 */  unkSubStruct* _4;
        /* 0x08 */ u16 _8;
        /* 0x0C */ s32 _C;
        /* 0x10 */ s32 _10;

        static MapCol* sCurMapCol;
    };

};

#endif
