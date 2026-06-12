#include "Sato/EnemyStrategy.hpp"

dummy_float_data()

EnemyStrategyInitFn** EnemyStrategy::getInitFunction(u32 index) {
    return &sInitFunctions[index];
}

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

void* EnemyStrategy::allocStrategy(u32 classSize, void* buffer, u32 bufferSize) {
    return buffer;
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

void EnemyStrategyDecorator::update() {
    // TODO: Figure out a way to match without this
    u32 padding[2];

    if (mTsuriStrategy == nullptr) {
        EnemyStrategy::update();
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
