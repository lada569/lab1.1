#include <iostream>
#include <istream>
#include <ostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>

class User {
protected:
    std::string name;
    int accessLevel;

public:
    User(const std::string& name, int accessLevel) : name(name), accessLevel(accessLevel) {
        if (name.empty()) throw std::invalid_argument("Name cannot be empty");
        if (accessLevel < 0) throw std::invalid_argument("Access level cannot be negative");
    }

    std::string getName() const { return name; }
    int getAccessLevel() const { return accessLevel; }

    void setName(const std::string& n) {
        if (n.empty()) throw std::invalid_argument("Name cannot be empty");
        name = n;
    }
    void setAccessLevel(int level) {
        if (level < 0) throw std::invalid_argument("Access level cannot be negative");
        accessLevel = level;
    }

    virtual void displayInfo() const {
        std::cout << "User: " << name << ", Access Level: " << accessLevel << std::endl;
    }
};

class Administrator : public User {
private:
    std::string role;

public:
    Administrator(const std::string& name, int accessLevel, const std::string& role) : User(name, accessLevel), role(role) {}
    void displayInfo() const override {
        std::cout << "Administrator: " << name << ", Role: " << role
            << ", Access Level: " << accessLevel << std::endl;
    }
    std::string getRole() const {
        return role;
    }
};

class Student : public User {
private:
    std::string group;

public:
    Student(const std::string& name, int accessLevel, const std::string& group) : User(name, accessLevel), group(group) {}
    void displayInfo() const override {
        std::cout << "Student: " << name << ", Group: " << group
            << ", Access Level: " << accessLevel << std::endl;
    }
    std::string getGroup() const {
        return group;
    }
};

class Teacher : public User {
private:
    std::string department;

public:
    Teacher(const std::string& name, int accessLevel, const std::string& department) : User(name, accessLevel), department(department) {}
    void displayInfo() const override {
        std::cout << "Teacher: " << name << ", Department: " << department
            << ", Access Level: " << accessLevel << std::endl;
    }
    std::string getDepartment() const {
        return department;
    }
};

class Resource {
private:
    std::string name;
    int requiredAccessLevel;

public:
    Resource(const std::string& name, int requiredAccessLevel) : name(name), requiredAccessLevel(requiredAccessLevel) {
        if (requiredAccessLevel < 0) throw std::invalid_argument("Access level must be non-negative");
    }

    std::string getName() const { return name; }
    int getRequiredAccessLevel() const { return requiredAccessLevel; }

    bool checkAccess(const User& user) const {
        return user.getAccessLevel() >= requiredAccessLevel;
    }

    void displayInfo() const {
        std::cout << "Resource: " << name << ", Access Level : " << requiredAccessLevel << std::endl;
    }
};

template <typename TUser, typename TResource>
class AccessControlSystem {
private:
    std::vector<std::shared_ptr<TUser>> users;
    std::vector<TResource> resources;

public:
    void addUser(const std::shared_ptr<TUser>& user) {
        users.push_back(user);
    }

    void addResource(const TResource& resource) {
        resources.push_back(resource);
    }


    std::shared_ptr<TUser> findUserById(size_t index) const {
        if (index < users.size()) return users[index];
        return nullptr;
    }

    void sortUsersByAccessLevel() {
        std::sort(users.begin(), users.end(), [](const std::shared_ptr<TUser>& a, const std::shared_ptr<TUser>& b) {
            return a->getAccessLevel() < b->getAccessLevel();
            });
    }

    void saveUsersToFile(const std::string& filename) const {
        std::ofstream out(filename);

        for (const auto& user : users) {
            if (auto s = std::dynamic_pointer_cast<Student>(user)) {
                out << "Student," << s->getName() << "," << s->getAccessLevel() << "," << s->getGroup() << "\n";
            }
            else if (auto t = std::dynamic_pointer_cast<Teacher>(user)) {
                out << "Teacher," << t->getName() << "," << t->getAccessLevel() << "," << t->getDepartment() << "\n";
            }
            else if (auto a = std::dynamic_pointer_cast<Administrator>(user)) {
                out << "Administrator," << a->getName() << "," << a->getAccessLevel() << "," << a->getRole() << "\n";
            }
        }
    }

    void loadUsersFromFile(const std::string& filename) {
        std::ifstream in(filename);
        std::string line;
        while (std::getline(in, line)) {
            std::stringstream ss(line);

            std::string type;
            std::getline(ss, type, ',');
            std::string name;
            std::getline(ss, name, ',');

            int access;
            char delim;

            ss >> access >> delim;


            if (type == "Student") {
                std::string group;
                std::getline(ss, group);
                users.push_back(std::make_shared<Student>(name, access, group));
            }
            else if (type == "Teacher") {
                std::string dept;
                std::getline(ss, dept);
                users.push_back(std::make_shared<Teacher>(name, access, dept));
            }
            else if (type == "Administrator") {
                std::string role;
                std::getline(ss, role);
                users.push_back(std::make_shared<Administrator>(name, access, role));
            }

        }
    }

    const std::vector<std::shared_ptr<TUser>>& getUsers() const { return users; }

    void saveResourcesToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file) throw std::runtime_error("Cannot open file to save resources");
        for (const auto& res : resources) {
            file << res.getName() << "," << res.getRequiredAccessLevel() << "\n";
        }
    }

    void loadResourcesFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) throw std::runtime_error("Cannot open file to load resources");
        resources.clear();

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name;
            int accessLevel;

            std::getline(iss, name, ',');
            iss >> accessLevel;

            resources.emplace_back(name, accessLevel);
        }
    }

    const std::vector<Resource>& getResources() const {
        return resources;
    }

    const Resource* findResourceById(int index) const {
        if (index >= 0 && index < resources.size()) {
            return &resources[index];
        }
        return nullptr;
    }

};

int main()
{
    AccessControlSystem<User, Resource> system;
    int choice;

    while (true) {
        std::cout << "\n=== University Access Control System ===\n";
        std::cout << "1. Add User\n";
        std::cout << "2. Add Resource\n";
        std::cout << "3. Check Access\n";
        std::cout << "4. Show All Users\n";
        std::cout << "5. Save Users to File\n";
        std::cout << "6. Load Users from File\n";
        std::cout << "7. Find User by ID\n";
        std::cout << "8. Sort Users by Access Level\n";
        std::cout << "9. Save Resources to File\n";
        std::cout << "10. Load Resources from File\n";
        std::cout << "11. Show All Resources\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        try {
            if (choice == 0) break;

            else if (choice == 1) {
                std::cout << "User type (1 - Student, 2 - Teacher, 3 - Administrator): ";
                int type;
                std::cin >> type;

                std::string name;
                int access;
                std::cout << "Name: ";
                std::cin >> name;
                std::cout << "Access Level: ";
                std::cin >> access;

                if (type == 1) {
                    std::string group;
                    std::cout << "Group: ";
                    std::cin >> group;
                    system.addUser(std::make_shared<Student>(name, access, group));
                }
                else if (type == 2) {
                    std::string dept;
                    std::cout << "Department: ";
                    std::cin >> dept;
                    system.addUser(std::make_shared<Teacher>(name, access, dept));
                }
                else if (type == 3) {
                    std::string role;
                    std::cout << "Role: ";
                    std::cin >> role;
                    system.addUser(std::make_shared<Administrator>(name, access, role));
                }
                else {
                    std::cout << "Invalid user type.\n";
                }

            }
            else if (choice == 2) {
                std::string name;
                int level;
                std::cout << "Resource Name: ";
                std::cin >> name;
                std::cout << "Required Access Level: ";
                std::cin >> level;
                system.addResource(Resource(name, level));
            }

            else if (choice == 3) {
                int userId, resourceId;
                std::cout << "Enter User ID: ";
                std::cin >> userId;
                std::cout << "Enter Resource ID: ";
                std::cin >> resourceId;

                auto user = system.findUserById(userId);
                const Resource* resource = system.findResourceById(resourceId);

                if (!user) {
                    std::cout << "User not found.\n";
                }
                else if (!resource) {
                    std::cout << "Resource not found.\n";
                }
                else {
                    if (resource->checkAccess(*user)) {
                        std::cout << "Access GRANTED to resource '" << resource->getName() << "'\n";
                    }
                    else {
                        std::cout << "Access DENIED to resource '" << resource->getName() << "'\n";
                    }
                }
            }

            else if (choice == 4) {
                const auto& users = system.getUsers();
                for (size_t i = 0; i < users.size(); ++i) {
                    std::cout << "ID: " << i << " | ";
                    users[i]->displayInfo();
                }
            }

            else if (choice == 5) {
                system.saveUsersToFile("users.txt");
                std::cout << "Users saved to users.txt\n";
            }

            else if (choice == 6) {
                system.loadUsersFromFile("users.txt");
                std::cout << "Users loaded from users.txt\n";
            }

            else if (choice == 7) {
                int id;
                std::cout << "Enter User ID: ";
                std::cin >> id;
                auto user = system.findUserById(id);
                if (user) user->displayInfo();
                else std::cout << "User not found.\n";
            }

            else if (choice == 8) {
                system.sortUsersByAccessLevel();
                std::cout << "Users sorted by access level.\n";
            }

            else if (choice == 9) {
                system.saveResourcesToFile("resources.txt");
                std::cout << "Resources saved to resources.txt\n";
            }
            else if (choice == 10) {
                system.loadResourcesFromFile("resources.txt");
                std::cout << "Resources loaded from resources.txt\n";
            }
            else if (choice == 11) {
                const auto& res = system.getResources();
                for (size_t i = 0; i < res.size(); ++i) {
                    std::cout << "ID: " << i << " | ";
                    res[i].displayInfo();
                }
            }

            else {
                std::cout << "Unknown command.\n";
            }

        }
        catch (const std::exception& ex) {
            std::cerr << "Error: " << ex.what() << "\n";
        }
    }

    std::cout << "Exiting program.\n";

}
