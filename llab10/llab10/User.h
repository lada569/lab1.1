#pragma once
#include <string>

class User {
protected:
    std::string name;
    int accessLevel;

public:
    User(const std::string& name, int accessLevel);

    std::string getName() const;
    int getAccessLevel() const;

    void setName(const std::string& name);
    void setAccessLevel(int accessLevel);

    virtual void displayInfo() const;
};
