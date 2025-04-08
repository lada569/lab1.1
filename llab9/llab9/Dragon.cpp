#include "Dragon.h"

Dragon::Dragon() : Monster("Dragon", 100, 20, 10) {}

void Dragon::attackCharacter(Character& character) {
    // сильный урон
    int damage;
    if (rand() % 3 == 0) {
        damage = attack * 2 - character.getDefense();
        std::cout << name << " (Dragon) breathes FIRE!\n";
    }
    else {
        damage = attack - character.getDefense();
        std::cout << name << " (Dragon) bites Hero.\n";
    }

    if (damage < 0) damage = 0;
    character.takeDamage(damage);
    std::cout << "Hero takes " << damage << " damage!\n";
}