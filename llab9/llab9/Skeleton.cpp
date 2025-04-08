#include "Skeleton.h"

Skeleton::Skeleton() : Monster("Skeleton", 40, 10, 3) {}

void Skeleton::attackCharacter(Character& character) {
    // урон, игнорирующий часть защиты
    int effectiveDefense = character.getDefense() / 2;
    int damage = attack - effectiveDefense;
    if (damage < 0) damage = 0;
    character.takeDamage(damage);
    std::cout << name << " (Skeleton) strikes through Hero's defenses for " << damage << " damage!\n";
}