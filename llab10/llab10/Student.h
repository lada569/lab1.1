#pragma once
#include "User.h"

class Student : public User {
private:
    std::string group;

public:
    Student(const std::string& name, int accessLevel, const std::string& group);
    void displayInfo() const override;
    std::string getGroup() const;
};
