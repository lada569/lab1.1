#pragma once
#include "User.h"

class Teacher : public User {
private:
    std::string department;

public:
    Teacher(const std::string& name, int accessLevel, const std::string& department);
    void displayInfo() const override;
    std::string getDepartment() const;
};
