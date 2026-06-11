#include "Koga/EnemyStrategy.hpp"

EnemyStrategy::EnemyStrategy() {
    unk4 = 0;
    unk8 = 0;
    unkC = 0;
    unkE = 0;
    unk10 = 0;
}

EnemyStrategy::~EnemyStrategy() { }
void EnemyStrategy::EnemyStrategy_vt_0C() { }

void EnemyStrategy::EnemyStrategy_vt_10() {
    if (unkC != 0xFFFF) {
        fn_800C2328();
    }
    EnemyStrategy_vt_1C();
    ++unk10;
}

void EnemyStrategy::EnemyStrategy_vt_1C() { }
void EnemyStrategy::EnemyStrategy_vt_20() { }
bool EnemyStrategy::EnemyStrategy_vt_14() { return false; }
void EnemyStrategy::EnemyStrategy_vt_18() { }

void EnemyStrategy::fn_800C2320(u16 value) {
    unkC = value;
}

void EnemyStrategy::fn_800C2328() {
    unkE = unkC;
    unkC = 0xFFFF;
    unk10 = 0;
    EnemyStrategy_vt_20();
}

u32 EnemyStrategy::fn_800C2370(u32 value) {
    return value;
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

void EnemyStrategyDecorator::EnemyStrategy_vt_10() {
    if (mNextStrategy == nullptr) {
        if (unkC != 0xFFFF) {
            unkE = unkC;
            unkC = 0xFFFF;
            unk10 = 0;
            EnemyStrategy_vt_20();
        }
        EnemyStrategy_vt_1C();
        ++unk10;
    } else {
        mNextStrategy->EnemyStrategy_vt_10();
        s32 value = mNextStrategy->getUnkE();
        if ((value >= 0x103) || (value < 0x100)) {
            return;
        }
        unk18 = value;
        mNextStrategy = nullptr;
    }
}
