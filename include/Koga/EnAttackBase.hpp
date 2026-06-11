#ifndef EN_ATTACK_BASE_H_
#define EN_ATTACK_BASE_H_

#include "types.h"
#include <JSystem/JORReflexible.hpp>
#include <Koga/CharacterEventObserver.hpp>
#include <Koga/EnemyStrategy.hpp>

class EnAttackBase : public EnemyStrategy, public Koga::CharacterEventObserver {
public:
    virtual ~EnAttackBase();
    virtual void* EnAttackBase_vt_70(); // Seems to be in a different TU than the destructor
};

#endif
