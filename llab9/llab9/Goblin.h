#pragma once
#include "Monster.h"

class Goblin : public Monster {
public:
    Goblin();
    void attackCharacter(Character& character) override;
};