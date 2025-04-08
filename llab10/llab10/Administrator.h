#pragma once
#include "User.h"

class Administrator : public User {
private:
    std::string role;

public:
    Administrator(const std::string& name, int accessLevel, const std::string& role);
    void displayInfo() const override;
    std::string getRole() const;
};
