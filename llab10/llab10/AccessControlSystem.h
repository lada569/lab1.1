#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

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

    void checkAccessAll() const {
        for (const auto& user : users) {
            for (const auto& resource : resources) {
                std::cout << user->getName() << " access to " << resource.getName()
                    << ": " << (resource.checkAccess(*user) ? "GRANTED" : "DENIED") << "\n";
            }
        }
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
