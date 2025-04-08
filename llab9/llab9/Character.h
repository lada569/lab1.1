#pragma once

#include <string>
#include "Inventory.h"
#include <iostream>
#include "Logger.h"


class Character {
private:
    std::string name;
    int hp;
    int attack;
    int defense;
    int level;
    int experience;
    Inventory inventory;
    Logger<std::string> logger;

public:
    Character(const std::string& name);
    void attackEnemy(class Monster& monster);
    void takeDamage(int amount);
    void heal(int amount);
    void gainExperience(int amount);
    void printInfo() const;
    int getHP() const;
    int getAttack() const;
    int getDefense() const;
    bool isAlive() const;
    void save(const std::string& filename) const;
    void load(const std::string& filename);
    void addItemAndApplyBonus(const std::string& item);
};
