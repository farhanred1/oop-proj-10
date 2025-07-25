// CargoManager.h
// Author: Alastair Gillyson Lamiao Madrid
#pragma once
#include "RecordManager.h"
#include "Cargo.h"

class CargoManager : public RecordManager<Cargo> {
public:
    // Constructor
    CargoManager();

    // Load Cargo records from CSV file
    void loadFromCSV(const std::string& path);
};