#include "Sato/EnemyStrategy.hpp"

EnemyStrategy::EnemyStrategy() {
    mpZako = nullptr;
    mpUserData = 0;
    mNextState = 0;
    mCurrentState = 0;
    mTimer = 0;
}

EnemyStrategy::~EnemyStrategy() { }
void EnemyStrategy::init() { }

void EnemyStrategy::update() {
    if (mNextState != 0xFFFF) {
        changeState();
    }
    doBehavior();
    ++mTimer;
}

void EnemyStrategy::doBehavior() { }
void EnemyStrategy::doBehaviorInit() { }
bool EnemyStrategy::vt_14() { return false; }
void EnemyStrategy::vt_18() { }

void EnemyStrategy::setNextState(u16 state) {
    mNextState = state;
}

void EnemyStrategy::changeState() {
    mCurrentState = mNextState;
    mNextState = 0xFFFF;
    mTimer = 0;
    doBehaviorInit();
}

u32 EnemyStrategy::fn_800C2370(u32 arg0, u32 arg1) {
    return arg1;
}

void EnemyStrategy::noOpDelete(void* ptr) {

}

EnemyStrategyDecorator::EnemyStrategyDecorator() {
    mTsuriStrategy = nullptr;
    unk18 = 0x100;
}

bool EnemyStrategyDecorator::setTsuriStrategy(EnemyStrategy* strategy) {
    if (mTsuriStrategy != nullptr) {
        return false;
    }
    mTsuriStrategy = strategy;
    return true;
}

// https://decomp.me/scratch/5NRr5
void EnemyStrategyDecorator::update() {
    if (mTsuriStrategy == nullptr) {
        if (mNextState != 0xFFFF) {
            mCurrentState = mNextState;
            mNextState = 0xFFFF;
            mTimer = 0;
            doBehaviorInit();
        }
        doBehavior();
        ++mTimer;
        return;
    }

    mTsuriStrategy->update();
    s32 value = mTsuriStrategy->getCurrentState();
    if ((value >= 0x103) || (value < 0x100)) {
        return;
    }
    unk18 = value;
    mTsuriStrategy = nullptr;
}
