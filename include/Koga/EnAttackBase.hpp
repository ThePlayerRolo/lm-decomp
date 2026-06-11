#ifndef EN_ATTACK_BASE_H_
#define EN_ATTACK_BASE_H_

#include <Koga/CharacterEventObserver.hpp>
#include <Sato/EnemyStrategy.hpp>

class EnAttackBase : public EnemyStrategy, public Koga::CharacterEventObserver {
public:
    /* 0x08 */ virtual ~EnAttackBase();
    /* 0x70 */ virtual void* vt_70(); // Seems to be in a different TU than the destructor
};

#endif
