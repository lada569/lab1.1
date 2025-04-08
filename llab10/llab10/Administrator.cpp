#include "Administrator.h"
#include <iostream>

Administrator::Administrator(const std::string& name, int accessLevel, const std::string& role)
    : User(name, accessLevel), role(role) {}

void Administrator::displayInfo() const {
    std::cout << "Administrator: " << name << ", Role: " << role
        << ", Access Level: " << accessLevel << std::endl;
}

std::string Administrator::getRole() const
{
    return role;
}
