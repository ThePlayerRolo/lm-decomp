#include "Koga/EnTypesManager.hpp"
#include "Koga/EnManager.hpp"
#include "Koga/ParamInst.hpp"
#include "types.h"


/* 
TODO splits.txt creates a cyclic dependency if I include the .data and .sdata sections with EnAttackBase.
May need to change / revise one of these but to not lose the section data:
	.data       start:0x80360D78 end:0x80361080
	.sdata      start:0x804D3938 end:0x804D3970
*/


// https://decomp.me/scratch/6Feh6
EnemyParam::EnemyParam() : 
    mLife(&mParams, 0, "mLife", mLife.calcKeyCode("mLife")),
    mHitDamange(&mParams, 0, "mHitDamange", mHitDamange.calcKeyCode("mHitDamange")),
    mSpeed(&mParams, 0, "mSpeed", mSpeed.calcKeyCode("mSpeed")),
    mSpeedUnseen(&mParams, 0, "mSpeedUnseen", mSpeedUnseen.calcKeyCode("mSpeedUnseen")),
    mSpeedFight(&mParams, 0, "mSpeedFight", mSpeedFight.calcKeyCode("mSpeedFight")),
    mEyesight(&mParams, 0, "mEyesight", mEyesight.calcKeyCode("mEyesight")),
    mLightBindFrame(&mParams, 0, "mLightBindFrame", mLightBindFrame.calcKeyCode("mLightBindFrame")),
    mMinLightBindRange(&mParams, 0, "mMinLightBindRange", mMinLightBindRange.calcKeyCode("mMinLightBindRange")),
    mMaxLightBindRange(&mParams, 0, "mMaxLightBindRange", mMaxLightBindRange.calcKeyCode("mMaxLightBindRange")),
    mNumAtKarakai(&mParams, 0, "mNumAtKarakai", mNumAtKarakai.calcKeyCode("mNumAtKarakai")),
    mNumAtOrooro(&mParams, 0, "mNumAtOrooro", mNumAtOrooro.calcKeyCode("mNumAtOrooro")),
    mHikiPower(&mParams, 0, "mHikiPower", mHikiPower.calcKeyCode("mHikiPower")),
    mEffectiveDeg(&mParams, 0, "mEffectiveDeg", mEffectiveDeg.calcKeyCode("mEffectiveDeg")),
    mTsuriHeight(&mParams, 0, "mTsuriHeight", mTsuriHeight.calcKeyCode("mTsuriHeight")),
    mDisappearFrame(&mParams, 0, "mDisappearFrame", mDisappearFrame.calcKeyCode("mDisappearFrame")),
    mAttackPattern1(&mParams, 0, "mAttackPattern1", mAttackPattern1.calcKeyCode("mAttackPattern1")),
    mActAfterAttackSu(&mParams, 0, "mActAfterAttackSu", mActAfterAttackSu.calcKeyCode("mActAfterAttackSu")),
    mActAfterAttackFa(&mParams, 0, "mActAfterAttackFa", mActAfterAttackFa.calcKeyCode("mActAfterAttackFa")),
    mTsuriType(&mParams, 0, "mTsuriType", mTsuriType.calcKeyCode("mTsuriType")),
    mElement(&mParams, 0, "mElement", mElement.calcKeyCode("mElement")),
    mCheckBox(&mParams, 0, "mCheckBox", mCheckBox.calcKeyCode("mCheckBox")),
    mNormalItemTblId(&mParams, 0, "mNormalItemTblId", mNormalItemTblId.calcKeyCode("mNormalItemTblId")),
    mTsuriItemTblId(&mParams, 0, "mTsuriItemTblId", mTsuriItemTblId.calcKeyCode("mTsuriItemTblId")),
    mPointerRange(&mParams, 0, "mPointerRange", mPointerRange.calcKeyCode("mPointerRange")),
    mBrightColor(&mParams, 0, "mBrightColor", mBrightColor.calcKeyCode("mBrightColor")),
    mAmbColor(&mParams, 0, "mAmbColor", mAmbColor.calcKeyCode("mAmbColor")) {
        // Maybe this isn't some default constructor based on mBrightColor / mAmbColor, since they both call fn_800D2FA0, which basically sets the defaults
        //  of these colors to -1 / 64, or maybe TBaseParam / TParamT needs its own inline base constructor?
    }

namespace Koga {
    EnTypesManager::EnTypesManager() {
        mEnParams = nullptr;
        mEnParams = new EnemyParam[0x17d];
    }

    EnTypesManager::~EnTypesManager() {
        delete [] mEnParams;
    }

    void EnTypesManager::newManager() {
        sManager = new EnTypesManager();
    }

    void EnTypesManager::deleteManager() {
        delete sManager;
        sManager = nullptr;
    }

    s32 EnTypesManager::getEnemyLife(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mLife.get();
    }

    s32 EnTypesManager::getEnemyHitDamage(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mHitDamange.get();
    }

    s32 EnTypesManager::getEnemySpeed(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mSpeed.get();
    }


    s32 EnTypesManager::getEnemySpeedUnseen(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mSpeedUnseen.get();
    }


    s32 EnTypesManager::getEnemySpeedFight(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mSpeedFight.get();
    }

    s32 EnTypesManager::getEnemyEyesight(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mEyesight.get();
    }

    s32 EnTypesManager::getEnemyLightBindFrame(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mLightBindFrame.get();
    }

    f32 EnTypesManager::getEnemyMinLightBindRange(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mMinLightBindRange.get();
    }

    f32 EnTypesManager::getEnemyMaxLightBindRange(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mMaxLightBindRange.get();
    }

    f32 EnTypesManager::getEnemyPointerRange(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mPointerRange.get();
    }
    
    s32 EnTypesManager::getEnemyNumAtKarakai(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mNumAtKarakai.get();
    }
    
    s32 EnTypesManager::getEnemyNumAtOrooro(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mNumAtOrooro.get();
    }
    
    f32 EnTypesManager::getEnemyHikiPower(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mHikiPower.get();
    }
    
    f32 EnTypesManager::getEnemyEffectiveDeg(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mEffectiveDeg.get();
    }
    
    f32 EnTypesManager::getEnemyTsuriHeight(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mTsuriHeight.get();
    }

    s32 EnTypesManager::getEnemyActAfterAttackSu(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mActAfterAttackSu.get();
    }

    s32 EnTypesManager::getEnemyActAfterAttackFa(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mActAfterAttackFa.get();
    }

    s32 EnTypesManager::getEnemyNormalItemTblId(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mNormalItemTblId.get();
    }
    
    s32 EnTypesManager::getEnemyTsuriItemTblId(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mTsuriItemTblId.get();
    }
    
    s32 EnTypesManager::getEnemyDisappearFrame(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mDisappearFrame.get();
    }

    // https://decomp.me/scratch/rwCN5
    JUtility::TColor EnTypesManager::getEnemyBrightColor(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mBrightColor.get();
    }
    
    // https://decomp.me/scratch/b6HLd
    JUtility::TColor EnTypesManager::getEnemyAmbColor(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mAmbColor.get();
    }

    s32 EnTypesManager::getEnemyAttackPattern1(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mAttackPattern1.get();
    }
    
    s32 EnTypesManager::getEnemyTsuriType(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mTsuriType.get();
    }
    
    s32 EnTypesManager::getEnemyElement(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mElement.get();
    }
    
    bool EnTypesManager::getEnemyCheckBox(int enemyIdx) {
        return getManager()->mEnParams[enemyIdx].mCheckBox.get() & 1;
    }
}
