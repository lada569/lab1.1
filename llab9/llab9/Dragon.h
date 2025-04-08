#pragma once
#include "Monster.h"

class Dragon : public Monster {
public:
    Dragon();
    void attackCharacter(class Character& character) override;
};
