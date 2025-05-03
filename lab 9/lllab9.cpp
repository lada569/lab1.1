#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>

template<typename T>
class Logger {
private:
    std::ofstream logFile;

public:
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios::app);
    }

    void log(const T& message) {
        if (logFile.is_open()) {
            logFile << message << std::endl;
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
};

class Inventory {
private:
    std::vector<std::string> items;

public:
    void addItem(const std::string& item) {
        items.push_back(item);
    }
    void removeItem(const std::string& item) {
        items.erase(std::remove(items.begin(), items.end(), item), items.end());
    }
    void printInventory() const {
        std::cout << "Inventory: ";
        for (const auto& item : items) {
            std::cout << item << ", ";
        }
        std::cout << "\n";
    }
};




class Monster {
protected:
    std::string name;
    int hp;
    int attack;
    int defense;

public:
    Monster(const std::string& name, int hp, int attack, int defense) : name(name), hp(hp), attack(attack), defense(defense) {}
    
    virtual void printInfo() const {
        std::cout << "Monster: " << name
            << "\nHP: " << hp
            << "\nAttack: " << attack
            << "\nDefense: " << defense << "\n";
    }
    int getHP() const {
        return hp;
    }
    int getAttack() const {
        return attack;
    }
    int getDefense() const {
        return defense;
    }
    void takeDamage(int amount) {
        hp -= amount;
        if (hp < 0) hp = 0;
    }
    bool isAlive() const {
        return hp > 0;
    }
    std::string getName() const {
    return name;
}
   
};

class Dragon : public Monster {
public:
    Dragon() : Monster("Dragon", 100, 20, 10) {}
    void printInfo() const override {
        std::cout << "Fire Dragon: " << name
            << "\nHP: " << hp
            << "\nAttack: " << attack
            << "\nDefense: " << defense << "\n";
    }
};

class Goblin : public Monster {
public:
    Goblin() : Monster("Goblin", 30, 5, 2) {}
    void printInfo() const override {
        std::cout << "Goblin: " << name
            << "\nHP: " << hp
            << "\nAttack: " << attack
            << "\nDefense: " << defense << "\n";
    }
};

class Skeleton : public Monster {
public:
    Skeleton() : Monster("Skeleton", 40, 10, 3) {}
    void printInfo() const override {
        std::cout << "Skeleton Archer: " << name
            << "\nHP: " << hp
            << "\nAttack: " << attack
            << "\nDefense: " << defense << "\n";
    }
};


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
    Character(const std::string& name) : name(name), hp(100), attack(10), defense(5), level(1), experience(0), logger("game.log") {
        std::srand(std::time(nullptr));
    }
    void attackEnemy(class Monster& monster) {
        int damage = attack - monster.getDefense();
        if (damage < 0) damage = 0;
        monster.takeDamage(damage);
        std::cout << name << " attacks " << monster.getName() << " for " << damage << " damage!\n";
        logger.log(name + " attacks " + monster.getName() + " for " + std::to_string(damage) + " damage");
    }
    void takeDamage(int amount) {
        hp -= amount;
        if (hp < 0) hp = 0;
    }
    void heal(int amount) {
        hp += amount;
        std::cout << name << " heals for " << amount << " HP.\n";
        logger.log(name + " heals for " + std::to_string(amount));
    }
    void gainExperience(int amount) {
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
    void printInfo() const {
        std::cout << "Character: " << name
            << "\nHP: " << hp
            << "\nAttack: " << attack
            << "\nDefense: " << defense
            << "\nLevel: " << level
            << "\nXP: " << experience << "\n";
        inventory.printInventory();
    }
    int getHP() const {
        return hp;
    }
    int getAttack() const {
        return attack;
    }
    int getDefense() const {
        return defense;
    }
    bool isAlive() const {
        return hp > 0;
    }
    void save(const std::string& filename) const {
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
    void load(const std::string& filename) {
        std::ifstream in(filename);
        if (in.is_open()) {
            in >> name >> hp >> attack >> defense >> level >> experience;
        }
    }
    void addItemAndApplyBonus(const std::string& item) {
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
};

class Game {
private:
    std::unique_ptr<Character> player;

public:
    Game() {
        player = std::make_unique<Character>("Hero");
    }
    void start() {
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
    void battle(Monster& monster) {
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
            throw std::exception();
        }
    }
    void saveProgress(const std::string& filename) {
        player->save(filename);
    }
    void loadProgress(const std::string& filename) {
        player->load(filename);
    }
};

int main()
{
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

