#include "Sato/EnemyStrategy.hpp"
#include <new>

static float lbl_80365A28[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.95f, 0.9f, 0.85f, 1.0f, 0.9f, 0.75f, 0.3f };

// This is a 99% match for most of the init functions, we just need all the classes
// defined and matched so it calls the right constructors.
template <class StrategyClass>
static void* enemyStrategyInit(void* buffer, u32 bufferSize) {
    void* ptr = EnemyStrategy::allocStrategy(sizeof(StrategyClass), buffer, bufferSize);
    return new (ptr) StrategyClass();
}

EnemyStrategyInitFn* EnemyStrategy::sInitFunctions[187] = {
    // Temporary placeholder to make sure the template matches
    enemyStrategyInit<EnemyStrategy>

    // TODO: All 187 instantiations...
};
