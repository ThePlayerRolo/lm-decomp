#ifndef ENEMY_STRATEGY_H_
#define ENEMY_STRATEGY_H_

#include "types.h"
#include <JSystem/JORReflexible.hpp>

class EnemyStrategy;

typedef bool (EnemyStrategy::*EnemyStrategyStateFn)();

// Each EnemyStrategy implementation has a static array of these structures.
// In their vt_1C and vt_20, they search for an entry with a stateIndex that matches their mCurrentState.
struct EnemyStrategyState {
    /* 0x00 */ u16 stateIndex;
    /* 0x02 */ u16 padding;
    /* 0x04 */ EnemyStrategyStateFn function1; // Called in overrides of EnemyStrategy::vt_20
    /* 0x10 */ EnemyStrategyStateFn function2; // Called in overrides of EnemyStrategy::vt_1C

    inline EnemyStrategyState(u16 _stateIndex,
        EnemyStrategyStateFn _function1,
        EnemyStrategyStateFn _function2
    ) : stateIndex(_stateIndex), padding(0), function1(_function1), function2(_function2) { }
};

class EnemyStrategy : public JORReflexible {
public:
    EnemyStrategy();
    /* 0x08 */ virtual ~EnemyStrategy();
    /* 0x0C */ virtual void init();
    /* 0x10 */ virtual void update();
    /* 0x14 */ virtual bool vt_14();
    /* 0x18 */ virtual void vt_18();
    /* 0x1C */ virtual void doBehavior();
    /* 0x20 */ virtual void doBehaviorInit();

    inline u16 getNextState() const { return mNextState; }
    inline u16 getCurrentState() const { return mCurrentState; }

    void setNextState(u16 state);
    void changeState();

    static u32 fn_800C2370(u32 arg0, u32 arg1);

    void operator delete(void* ptr) {
        noOpDelete(ptr);
    }
protected:
    /* 0x04 */ void* mpZako;
    /* 0x08 */ void* mpUserData;
    /* 0x0C */ u16 mNextState; // 0xFFFF = end strategy
    /* 0x0E */ u16 mCurrentState;
    /* 0x10 */ u32 mTimer;
private:
    static void noOpDelete(void* ptr);
};

class EnemyStrategyDecorator : public EnemyStrategy {
public:
    EnemyStrategyDecorator();
    bool setTsuriStrategy(EnemyStrategy* strategy);

    virtual void update();
private:
    /* 0x14 */ EnemyStrategy* mTsuriStrategy;
    /* 0x18 */ u16 unk18;
};

#endif
