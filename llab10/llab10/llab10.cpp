#include <iostream>
#include "Student.h"
#include "Teacher.h"
#include "Administrator.h"
#include "Resource.h"
#include "AccessControlSystem.h"

int main() {
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
    return 0;
}
