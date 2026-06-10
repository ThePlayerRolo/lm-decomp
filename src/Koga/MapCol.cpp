#include "Koga/MapCol.hpp"
#include "JSystem/JGeometry/JGVec3.hpp"
#include "Koga/ToolData.hpp"

dummy_float_data()

static f32 dummy_float_data2[8] = {1.0f, 0.95f, 0.9f, 0.85f, 1.0f, 0.9f, 0.75f, 0.3f};

extern Koga::ToolData* fn_800B9F50(const char*);
extern int fn_8018D474(u16, u16, u16);

s32 lbl_804D2D18 = 0;

namespace Koga {

    MapCol::~MapCol() { }

    void MapCol::newMapCol() {
        sCurMapCol = new MapCol();
    }

    void MapCol::deleteMapCol() {
        delete sCurMapCol;
        sCurMapCol = nullptr;
    }

    void MapCol::load(void* param_1, void* param_2) {
        _4 = (unkSubStruct*)param_1;
        if (fn_800B9F50("SoundPolygonInfo") != nullptr) {
            Koga::ToolData* soundPolygonInfo = fn_800B9F50("SoundPolygonInfo");

            _C = soundPolygonInfo->searchItemInfo("sound_material");
            _10 = soundPolygonInfo->searchItemInfo("sound_echo_switch");
        }
    }

    // https://decomp.me/scratch/O6zkC
    JGeometry::TVec3f* MapCol::fn_800BBBE0(JGeometry::TVec3f* param_1) {
        JGeometry::TVec3f stack_18;
        s32* val2;

        if (fn_800BBCA8(param_1, stack_18) == false) {
            val2 = &lbl_804D2D18;
        } else {
            val2 = fn_800BBD54(stack_18);
        }

        return &_4->_0[*val2];
    }

    // https://decomp.me/scratch/cGlAK
    bool MapCol::fn_800BBCA8(JGeometry::TVec3f* param_1, JGeometry::TVec3f& param_2) {
        PSVECSubtract(param_1, &_4->_0[1], &param_2);

        return vecCheckto_4(param_2);
    }

    // https://decomp.me/scratch/JJHFz
    f32 MapCol::fn_800BBE2C(JGeometry::TVec3f& param_1) {
        JGeometry::TVec3f stack_d8;
        PSVECSubtract(&param_1, &_4->_0[1], &stack_d8);
        bool vecCheck4 = vecCheckto_4(stack_d8);

        if (!vecCheck4)
            return 32000.0f;

        for (; stack_d8.y > _4->_0[2].y; stack_d8.y += _4->_0[2].y) {
            bool bVar5 = false;

            // int iVar7 =(int)(_4[2].x / _4[0].x);
            // int iVar1 =(int)(stack_d8.z / _4[0].z);
            // int iVar2 =(int)(stack_d8.y / _4[0].y);
            // int iVar3 =(int)(_4[2].y / _4[0].y);
            // int iVar4 =(int)(stack_d8.x / _4[0].x);
            // iVar7++;
        }
    }

    void MapCol::fn_800BC898() { }

    void MapCol::fn_800BC89C(s32 param_1) {
        _8 |= 1 << param_1;
    }

    void MapCol::fn_800BC8B4(s32 param_1) {
        _8 &= ~(1 << param_1);
    }

    // https://decomp.me/scratch/KOzK8
    int MapCol::fn_800BC8CC(s16 param_1) {
        if (param_1 < 0)
            return 0;
        if (_10 < 0)
            return 0;
        if (_C < 0)
            return 0;

        Koga::ToolData* soundPolygonInfo = fn_800B9F50("SoundPolygonInfo");
        u32 p1 = param_1;
        u32 firstVal = soundPolygonInfo->getUnsignedValue< u32 >(_C, param_1);
        u32 secondVal = soundPolygonInfo->getUnsignedValue< u32 >(_10, param_1);

        return fn_8018D474(firstVal, secondVal, 0);
    }

    ToolData* MapCol::getPolygonInfo() {
        return fn_800B9F50("PolygonInfo");
    }
};  // namespace Koga
