#pragma once
#include <string>
#include "User.h"
#include <iostream>

class Resource {
private:
    std::string name;
    int requiredAccessLevel;

public:
    Resource(const std::string& name, int requiredAccessLevel);

    std::string getName() const;
    int getRequiredAccessLevel() const;

    bool checkAccess(const User& user) const;

    void displayInfo() const;
};
