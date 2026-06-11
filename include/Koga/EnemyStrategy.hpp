#ifndef ENEMY_STRATEGY_H_
#define ENEMY_STRATEGY_H_

#include "types.h"
#include <JSystem/JORReflexible.hpp>

class EnemyStrategy;

typedef bool (EnemyStrategy::*EnemyStrategyStateFn)();

// Each EnemyStrategy implementation has a static array of these structures.
struct EnemyStrategyState {
    /* 0x00 */ u16 stateIndex; // Compared with EnemyStrategy::mCurrentState
    /* 0x02 */ u16 padding;
    /* 0x04 */ EnemyStrategyStateFn function1; // Called in overrides of EnemyStrategy_vt_20
    /* 0x10 */ EnemyStrategyStateFn function2; // Called in overrides of EnemyStrategy_vt_1C

    inline EnemyStrategyState(u16 _stateIndex,
        EnemyStrategyStateFn _function1,
        EnemyStrategyStateFn _function2
    ) : stateIndex(_stateIndex), padding(0), function1(_function1), function2(_function2) { }
};

class EnemyStrategy : public JORReflexible {
public:
    EnemyStrategy();
    virtual ~EnemyStrategy();
    virtual void EnemyStrategy_vt_0C();
    virtual void EnemyStrategy_vt_10();
    virtual bool EnemyStrategy_vt_14();
    virtual void EnemyStrategy_vt_18();
    virtual void EnemyStrategy_vt_1C();
    virtual void EnemyStrategy_vt_20();

    inline u16 getNextState() const { return mNextState; }
    inline u16 getCurrentState() const { return mCurrentState; }

    void setNextState(u16 state);

    static u32 fn_800C2370(u32 arg0, u32 arg1);
protected:
    /* 0x04 */ void* unk4;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u16 mNextState; // 0xFFFF = end strategy
    /* 0x0E */ u16 mCurrentState;
    /* 0x10 */ u32 unk10;
private:
    void fn_800C2328();
    static void noOpDelete(void* ptr);
public:
    void operator delete(void* ptr) {
        noOpDelete(ptr);
    }
};

class EnemyStrategyDecorator : public EnemyStrategy {
public:
    EnemyStrategyDecorator();
    bool setNextStrategy(EnemyStrategy* strategy);

    virtual void EnemyStrategy_vt_10();
    virtual ~EnemyStrategyDecorator(); // The destructor might be defined in another TU, not EnemyStrategy.cpp
private:
    /* 0x14 */ EnemyStrategy* mNextStrategy;
    /* 0x18 */ u16 unk18;
};

#endif
