#include "Teacher.h"
#include <iostream>

Teacher::Teacher(const std::string& name, int accessLevel, const std::string& department)
    : User(name, accessLevel), department(department) {}

void Teacher::displayInfo() const {
    std::cout << "Teacher: " << name << ", Department: " << department
        << ", Access Level: " << accessLevel << std::endl;
}

std::string Teacher::getDepartment() const
{
    return department;
}
