#include "Goblin.h"

Goblin::Goblin() : Monster("Goblin", 30, 5, 2) {}

void Goblin::attackCharacter(Character& character) {
    // слабый удар
    int damage = (attack / 2) - character.getDefense();
    if (damage < 0) damage = 0;
    character.takeDamage(damage);
    std::cout << name << " (Goblin) quickly slashes Hero for " << damage << " damage!\n";
}