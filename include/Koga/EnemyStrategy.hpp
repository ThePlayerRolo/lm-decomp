#ifndef ENEMY_STRATEGY_H_
#define ENEMY_STRATEGY_H_

#include "types.h"
#include <JSystem/JORReflexible.hpp>

// TODO: No idea what this is for. It's an empty function that does nothing.
extern "C" void fn_800C2378(void* ptr);

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

    inline u16 getUnkE() const { return unkE; }

    void fn_800C2320(u16 value);
    u32 fn_800C2370(u32 value);
protected:
    u32 unk4;
    u32 unk8;
    u16 unkC;
    u16 unkE;
    u32 unk10;
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
    EnemyStrategy* mNextStrategy;
    u16 unk18;
    u16 unk20;
};

#endif
