#pragma once

#include "Character.h"
#include "Dragon.h"
#include "Goblin.h"
#include "Skeleton.h"


class Game {
private:
    std::unique_ptr<Character> player;

public:
    Game();
    void start();
    void battle(Monster& monster);
    void saveProgress(const std::string& filename);
    void loadProgress(const std::string& filename);
};



