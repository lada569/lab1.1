#include "Game.h"

int main() {
    Game game;


    try {
    while (true) {
            std::cout << "\n==== Menu ====\n"
                << "1. Start Game\n"
                << "2. Load Game\n"
                << "3. Save Game\n"
                << "4. Exit\n> ";
            int input;
            std::cin >> input;

            switch (input) {
            case 1: game.start(); break;
            case 2: game.loadProgress("save.txt"); break;
            case 3: game.saveProgress("save.txt"); break;
            case 4: std::cout << "Goodbye!\n"; return 0;
            default: std::cout << "Invalid input.\n";
            }
        }
    }
    catch (std::exception e) {
        std::cout << e.what();
    }
}
