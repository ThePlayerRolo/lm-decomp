#ifndef EN_TYPES_MANAGER_H_
#define EN_TYPES_MANAGER_H_

#include <dolphin/types.h>
#include <types.h>
#include <JSystem/JORReflexible.hpp>

#include "JSystem/JUtility/JUTColor.hpp"
#include "Koga/ParamInst.hpp"
#include "Koga/Params.hpp"


class ToolDataRef;
class unkEnCharacter;

class EnemyParam {
    public:
        EnemyParam();

    public:
        /* 0x000 */ TParams mParams;
        /* 0x00C */ TParamT<s32> mLife;
        /* 0x020 */ TParamT<s32> mHitDamange;
        /* 0x034 */ TParamT<s32> mSpeed;
        /* 0x048 */ TParamT<s32> mSpeedUnseen;
        /* 0x05C */ TParamT<s32> mSpeedFight;
        /* 0x070 */ TParamT<s32> mEyesight;
        /* 0x084 */ TParamT<s32> mLightBindFrame;
        /* 0x098 */ TParamT<f32> mMinLightBindRange;
        /* 0x0AC */ TParamT<f32> mMaxLightBindRange;
        /* 0x0C0 */ TParamT<s32> mNumAtKarakai;
        /* 0x0D4 */ TParamT<s32> mNumAtOrooro;
        /* 0x0E8 */ TParamT<f32> mHikiPower;
        /* 0x0FC */ TParamT<f32> mEffectiveDeg;
        /* 0x110 */ TParamT<f32> mTsuriHeight;
        /* 0x124 */ TParamT<s32> mDisappearFrame;
        /* 0x138 */ TParamT<s32> mAttackPattern1;
        /* 0x14C */ TParamT<s32> mActAfterAttackSu;
        /* 0x160 */ TParamT<s32> mActAfterAttackFa;
        /* 0x174 */ TParamT<s32> mTsuriType;
        /* 0x188 */ TParamT<s32> mElement;
        /* 0x19C */ TParamT<u16> mCheckBox;
        /* 0x1B0 */ TParamT<s32> mNormalItemTblId;
        /* 0x1C4 */ TParamT<s32> mTsuriItemTblId;
        /* 0x1D8 */ TParamT<f32> mPointerRange;
        /* 0x1EC */ TParamT<JUtility::TColor> mBrightColor;
        /* 0x200 */ TParamT<JUtility::TColor> mAmbColor;
        /* 0x214 */ s32 _214; // Unknown
};

namespace Koga {
    class EnTypesManager : public JORReflexible {
    public:
        inline EnTypesManager();
        /* 0x08 */ virtual ~EnTypesManager();

        static void newManager();
        static void deleteManager();
        static EnTypesManager* getManager() { return sManager; }

        void loadCTPParams(); // Loads "/param/ctp/%s.prm" in some sprintf loop

        // Various EnemyParam helpers
        static s32 getEnemyLife(int);
        static s32 getEnemyHitDamage(int);
        static s32 getEnemySpeed(int);
        static s32 getEnemySpeedUnseen(int);
        static s32 getEnemySpeedFight(int);
        static s32 getEnemyEyesight(int);
        static s32 getEnemyLightBindFrame(int);
        static f32 getEnemyMinLightBindRange(int);
        static f32 getEnemyMaxLightBindRange(int);
        static f32 getEnemyPointerRange(int);
        static s32 getEnemyNumAtKarakai(int);
        static s32 getEnemyNumAtOrooro(int);
        static f32 getEnemyHikiPower(int);
        static f32 getEnemyEffectiveDeg(int);
        static f32 getEnemyTsuriHeight(int);
        static s32 getEnemyActAfterAttackSu(int);
        static s32 getEnemyActAfterAttackFa(int);
        static s32 getEnemyNormalItemTblId(int);
        static s32 getEnemyTsuriItemTblId(int);
        static s32 getEnemyDisappearFrame(int);
        static JUtility::TColor getEnemyBrightColor(int);
        static JUtility::TColor getEnemyAmbColor(int);
        static s32 getEnemyAttackPattern1(int);
        static s32 getEnemyTsuriType(int);
        static s32 getEnemyElement(int);
        static bool getEnemyCheckBox(int);
    public:
        /* 0x04 */ EnemyParam* mEnParams;

        static EnTypesManager* sManager;
    };

};

// All of these are referenced in EnManager. No arg types or return types are guaranteed.
s32 fn_800DAB18(char*); // Might be static?
s32 fn_800DABA4(ToolDataRef); // Might be static?
s32 fn_800DAC84(s32);
void* fn_800DAD00(void*);
unkEnCharacter* fn_800DB034(void*);
void* fn_800DB06C(int);

#endif
