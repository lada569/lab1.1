#include "Character.h"
#include "Monster.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

Character::Character(const std::string& name)
    : name(name), hp(100), attack(10), defense(5), level(1), experience(0), logger("game.log") {
    std::srand(std::time(nullptr));
}

void Character::attackEnemy(Monster& monster) {
    int damage = attack - monster.getDefense();
    if (damage < 0) damage = 0;
    monster.takeDamage(damage);
    std::cout << name << " attacks " << monster.getName() << " for " << damage << " damage!\n";
    logger.log(name + " attacks " + monster.getName() + " for " + std::to_string(damage) + " damage");
}


void Character::heal(int amount) {
    hp += amount;
    std::cout << name << " heals for " << amount << " HP.\n";
    logger.log(name + " heals for " + std::to_string(amount));
}

void Character::gainExperience(int amount) {
    experience += amount;
    std::cout << name << " gains " << amount << " XP.\n";
    if (experience >= level * 100) {
        experience = 0;
        level++;
        attack += 5;
        defense += 3;
        hp += 20;
        std::cout << name << " leveled up to " << level << "!\n";
        logger.log(name + " leveled up to " + std::to_string(level));
    }
}

void Character::printInfo() const {
    std::cout << "Character: " << name
        << "\nHP: " << hp
        << "\nAttack: " << attack
        << "\nDefense: " << defense
        << "\nLevel: " << level
        << "\nXP: " << experience << "\n";
    inventory.printInventory();
}

int Character::getHP() const {
    return hp;
}

void Character::save(const std::string& filename) const {
    std::ofstream out(filename);
    if (out.is_open()) {
        out << name << '\n'
            << hp << '\n'
            << attack << '\n'
            << defense << '\n'
            << level << '\n'
            << experience << '\n';
    }
}

void Character::load(const std::string& filename) {
    std::ifstream in(filename);
    if (in.is_open()) {
        in >> name >> hp >> attack >> defense >> level >> experience;
    }
}

void Character::addItemAndApplyBonus(const std::string& item) {
    inventory.addItem(item);
    if (item.find("Attack") != std::string::npos) {
        attack += 3;
        std::cout << "Item bonus: +3 Attack!\n";
    }
    else if (item.find("Defense") != std::string::npos) {
        defense += 2;
        std::cout << "Item bonus: +2 Defense!\n";
    }
}

void Character::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}

int Character::getAttack() const {
    return attack;
}

int Character::getDefense() const {
    return defense;
}

bool Character::isAlive() const {
    return hp > 0;
}
