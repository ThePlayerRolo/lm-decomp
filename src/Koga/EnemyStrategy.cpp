#include "Koga/EnemyStrategy.hpp"

EnemyStrategy::EnemyStrategy() {
    unk4 = nullptr;
    unk8 = 0;
    mNextState = 0;
    mCurrentState = 0;
    unk10 = 0;
}

EnemyStrategy::~EnemyStrategy() { }
void EnemyStrategy::EnemyStrategy_vt_0C() { }

void EnemyStrategy::EnemyStrategy_vt_10() {
    if (mNextState != 0xFFFF) {
        fn_800C2328();
    }
    EnemyStrategy_vt_1C();
    ++unk10;
}

void EnemyStrategy::EnemyStrategy_vt_1C() { }
void EnemyStrategy::EnemyStrategy_vt_20() { }
bool EnemyStrategy::EnemyStrategy_vt_14() { return false; }
void EnemyStrategy::EnemyStrategy_vt_18() { }

void EnemyStrategy::setNextState(u16 state) {
    mNextState = state;
}

void EnemyStrategy::fn_800C2328() {
    mCurrentState = mNextState;
    mNextState = 0xFFFF;
    unk10 = 0;
    EnemyStrategy_vt_20();
}

u32 EnemyStrategy::fn_800C2370(u32 arg0, u32 arg1) {
    // I have no idea what this is for.
    // There's a huge list of function pointers at lbl_80365A60, and they all call this.
    return arg1;
}

void EnemyStrategy::noOpDelete(void* ptr) {

}

EnemyStrategyDecorator::EnemyStrategyDecorator() {
    mNextStrategy = nullptr;
    unk18 = 0x100;
}

bool EnemyStrategyDecorator::setNextStrategy(EnemyStrategy* strategy) {
    if (mNextStrategy != nullptr) {
        return false;
    }
    mNextStrategy = strategy;
    return true;
}

// https://decomp.me/scratch/5NRr5
void EnemyStrategyDecorator::EnemyStrategy_vt_10() {
    if (mNextStrategy == nullptr) {
        if (mNextState != 0xFFFF) {
            mCurrentState = mNextState;
            mNextState = 0xFFFF;
            unk10 = 0;
            EnemyStrategy_vt_20();
        }
        EnemyStrategy_vt_1C();
        ++unk10;
        return;
    }

    mNextStrategy->EnemyStrategy_vt_10();
    s32 value = mNextStrategy->getCurrentState();
    if ((value >= 0x103) || (value < 0x100)) {
        return;
    }
    unk18 = value;
    mNextStrategy = nullptr;
}
