#pragma once
#include "Monster.h"

class Skeleton : public Monster {
public:
    Skeleton();
    void attackCharacter(Character& character) override;
};

