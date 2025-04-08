#include "User.h"
#include <stdexcept>
#include <iostream>

User::User(const std::string& name, int accessLevel)
    : name(name), accessLevel(accessLevel) {
    if (name.empty()) throw std::invalid_argument("Name cannot be empty");
    if (accessLevel < 0) throw std::invalid_argument("Access level cannot be negative");
}

std::string User::getName() const { return name; }
int User::getAccessLevel() const { return accessLevel; }

void User::setName(const std::string& n) {
    if (n.empty()) throw std::invalid_argument("Name cannot be empty");
    name = n;
}
void User::setAccessLevel(int level) {
    if (level < 0) throw std::invalid_argument("Access level cannot be negative");
    accessLevel = level;
}

void User::displayInfo() const
{
    std::cout << "User: " << name << ", Access Level: " << accessLevel << std::endl;
}
