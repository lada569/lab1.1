#include "Monster.h"
#include "Character.h"
#include <iostream>

Monster::Monster(const std::string& name, int hp, int attack, int defense)
    : name(name), hp(hp), attack(attack), defense(defense) {}

void Monster::printInfo() const {
    std::cout << "Monster: " << name
        << "\nHP: " << hp
        << "\nAttack: " << attack
        << "\nDefense: " << defense << "\n";
}

void Monster::attackCharacter(Character& character) {
    int damage = attack - character.getDefense();
    if (damage < 0) damage = 0;
    character.takeDamage(damage);
    std::cout << name << " attacks " << "Hero"
        << " for " << damage << " damage!\n";
}

int Monster::getHP() const {
    return hp;
}

void Monster::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}

int Monster::getAttack() const {
    return attack;
}

int Monster::getDefense() const {
    return defense;
}

bool Monster::isAlive() const {
    return hp > 0;
}

std::string Monster::getName() const {
    return name;
}






