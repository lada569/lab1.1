#include "Inventory.h"
#include <iostream>
#include <algorithm>

void Inventory::addItem(const std::string& item) {
    items.push_back(item);
}

void Inventory::removeItem(const std::string& item) {
    items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

void Inventory::printInventory() const {
    std::cout << "Inventory: ";
    for (const auto& item : items) {
        std::cout << item << ", ";
    }
    std::cout << "\n";
}

