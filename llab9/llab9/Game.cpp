#include "Game.h"
#include "Logger.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game() {
    player = std::make_unique<Character>("Hero");
}


void Game::start() {
    std::cout << "Welcome to the Adventure Game!\n";

    while (true) {
        
        std::cout << "\n==== ============== ====";
        std::cout << "\n==== Character Info ====\n\n";
        player->printInfo();

        std::cout << "\nChoose a monster to fight:\n"
            "1. Goblin\n2. Dragon\n3. Skeleton\n4. Back to menu\n> ";
        int choice;
        std::cin >> choice;

        std::unique_ptr<Monster> monster;
        switch (choice) {
        case 1: monster = std::make_unique<Goblin>(); break;
        case 2: monster = std::make_unique<Dragon>(); break;
        case 3: monster = std::make_unique<Skeleton>(); break;
        case 4: return;
        default: std::cout << "Invalid option.\n"; continue;
        }
    
        std::cout << "\n==== Enemy Info ====\n";
        monster->printInfo();
  
        std::cout << "\nBegin battle? (y/n): ";
        char confirm;
        std::cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            battle(*monster);
        }
        else {
            std::cout << "You chose to avoid the fight.\n";
        }
    }
}

void Game::battle(Monster& monster) {
    Logger<std::string> logger("game.log");

    while (player->isAlive() && monster.isAlive()) {
        std::cout << "\n-- Battle Turn --\n";
        std::cout << "\n- Character -\n";
        player->printInfo();

        std::cout << "\n- Monster -\n";
        monster.printInfo();

        std::cout << "\n- Fight -\n";
        player->attackEnemy(monster);

        if (monster.isAlive()) {
            int damage = monster.getAttack() - player->getDefense();
            if (damage < 0) damage = 0;
            player->takeDamage(damage);
            std::cout << monster.getName() << " attacks Hero for " << damage << " damage!\n";
            logger.log(monster.getName() + " attacks Hero for " + std::to_string(damage) + " damage!");
        }
    }

    if (player->isAlive()) {
        std::cout << "Victory! You defeated the " << monster.getName() << "!\n";
        logger.log(monster.getName() + " defeated");
        player->gainExperience(100);

        std::string loot = (std::rand() % 2 == 0) ? "Sword of Attack +3" : "Shield of Defense +2";
        std::cout << "You found an item: " << loot << "!\n";
        logger.log(loot + " add to inventory");
        player->addItemAndApplyBonus(loot);
    }
    else {
        std::cout << "You were defeated by the " << monster.getName() << ".\n";
        logger.log("Character died");
        throw std::exception("End of the game!");
    }
}


void Game::saveProgress(const std::string& filename) {
    player->save(filename);
}

void Game::loadProgress(const std::string& filename) {
    player->load(filename);
}
