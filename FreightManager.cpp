// FreightManager.cpp
#include "FreightManager.h"
#include "FileManager.h"

// Constructor
FreightManager::FreightManager() {}

void FreightManager::loadFromCSV(const std::string& path) {
    auto rows = FileManager::loadCSV(path);
    for (const auto& row : rows) {
        if (row.size() >= 3) {
            Freight f(row[0], row[1], std::stoi(row[2]), row[3]);
            this->add(f);
        }
    }
}