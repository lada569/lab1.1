#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Entity {
protected:
    std::string name;
    int health;
    int attackPower;
    int defense;

public:
    Entity(const std::string& n, int h, int a, int d)
        : name(n), health(h), attackPower(a), defense(d) {
    }

    const std::string& getName()    const { return name; }
    int                getDefense() const { return defense; }
    int                getHealth()  const { return health; }

    virtual void takeDamage(int amount) {
        health -= amount;
    }

    virtual void attack(Entity& target) {
        int damage = attackPower - target.getDefense();
        if (damage > 0) {
            target.takeDamage(damage);
            std::cout << name << " attacks "
                << target.getName()
                << " for " << damage << " damage!\n";
        }
        else {
            std::cout << name << " attacks "
                << target.getName()
                << ", but it has no effect!\n";
        }
    }

    virtual void displayInfo() const {
        std::cout << "Name: " << name
            << ", HP: " << health
            << ", Attack: " << attackPower
            << ", Defense: " << defense
            << std::endl;
    }

    virtual void heal(int amount) {
        health += amount;
        std::cout << name << " heals for " << amount << " HP.\n";
    }

    virtual ~Entity() {}
};

class Character : public Entity {
public:
    using Entity::Entity;

    void attack(Entity& target) override {
        int damage = attackPower - target.getDefense();
        if (damage > 0) {
            if (rand() % 100 < 20) {
                damage *= 2;
                std::cout << "Critical hit! ";
            }
            target.takeDamage(damage);
            std::cout << name << " attacks "
                << target.getName()
                << " for " << damage << " damage!\n";
        }
        else {
            std::cout << name << " attacks "
                << target.getName()
                << ", but it has no effect!\n";
        }
    }

    void heal(int amount) override {
        health += amount;
        std::cout << name << " uses a potion and heals for "
            << amount << " HP.\n";
    }

    void displayInfo() const override {
        std::cout << "Character: " << name
            << ", HP: " << health
            << ", Attack: " << attackPower
            << ", Defense: " << defense
            << std::endl;
    }
};

class Monster : public Entity {
public:
    using Entity::Entity;

    void attack(Entity& target) override {
        int damage = attackPower - target.getDefense();
        if (damage > 0) {
            if (rand() % 100 < 30) {
                damage += 5;
                std::cout << "Poisonous attack! ";
            }
            target.takeDamage(damage);
            std::cout << name << " attacks "
                << target.getName()
                << " for " << damage << " damage!\n";
        }
        else {
            std::cout << name << " attacks "
                << target.getName()
                << ", but it has no effect!\n";
        }
    }

    void displayInfo() const override {
        std::cout << "Monster: " << name
            << ", HP: " << health
            << ", Attack: " << attackPower
            << ", Defense: " << defense
            << std::endl;
    }
};

class Boss : public Monster {
public:
    using Monster::Monster;

    void attack(Entity& target) override {
        int damage = attackPower - target.getDefense();
        if (damage > 0) {
            if (rand() % 100 < 40) {
                damage += 10;
                std::cout << "Fire Strike! ";
            }
            target.takeDamage(damage);
            std::cout << name << " attacks "
                << target.getName()
                << " for " << damage << " damage!\n";
        }
        else {
            std::cout << name << " uses Fire Strike on "
                << target.getName()
                << ", but it has no effect!\n";
        }
    }

    void displayInfo() const override {
        std::cout << "Boss: " << name
            << ", HP: " << health
            << ", Attack: " << attackPower
            << ", Defense: " << defense
            << std::endl;
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    Character hero("Hero", 100, 20, 10);
    Monster monstrik("Monstrik", 50, 15, 5);
    Boss megaboss("MegaBoss", 200, 30, 25);

    Entity* entities[] = { &hero, &monstrik, &megaboss };

    std::cout << "=== Entity Info ===\n";
    for (auto e : entities) e->displayInfo();

    std::cout << "\n=== Battle ===\n";
    hero.attack(monstrik);
    monstrik.attack(hero);
    megaboss.attack(hero);

    std::cout << "\n=== Healing ===\n";
    hero.heal(25);
    hero.displayInfo();

    return 0;
}
