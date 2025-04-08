#pragma once

#include <string>
#include <iostream>
#include "Character.h"

class Monster {
protected:
    std::string name;
    int hp;
    int attack;
    int defense;

public:
    Monster(const std::string& name, int hp, int attack, int defense);
    virtual void attackCharacter(Character& character);
    virtual void printInfo() const;
    int getHP() const;
    int getAttack() const;
    int getDefense() const;
    void takeDamage(int amount);
    bool isAlive() const;
    virtual ~Monster() = default;
    std::string getName() const;
};