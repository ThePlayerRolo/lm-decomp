#include "Koga/GameMode.hpp"

Koga::GameMode* Koga::GameModeBase::sCurrentGameMode = nullptr;
int Koga::GameModeBase::sGameModeCount = 0;

Koga::GameMode::GameMode() { }
Koga::GameMode::~GameMode() { }

void Koga::GameMode::vt_C() { }
void Koga::GameMode::vt_10() { }
void Koga::GameMode::vt_14() { }
void Koga::GameMode::vt_18() { }

Koga::GameModeBase::GameModeBase() {
    incrementGameModeCount();
}

void Koga::GameModeBase::incrementGameModeCount() {
    Koga::GameModeBase::sGameModeCount += 1;
}
