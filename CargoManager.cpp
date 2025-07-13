// CargoManager.cpp
#include "CargoManager.h"
#include "FileManager.h"

// Constructor
CargoManager::CargoManager() {}

void CargoManager::loadFromCSV(const std::string& path) {
    auto rows = FileManager::loadCSV(path);
    for (const auto& row : rows) {
        if (row.size() >= 3) {
            Cargo c(row[0], row[1], std::stoi(row[2]), std::stoi(row[3]));
            this->add(c);
        }
    }
}