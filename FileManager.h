// FileManager.h
#pragma once
#include "Freight.h"
#include "Cargo.h"
#include "ScheduleManager.h"

class FileManager {
public:
    // Load Freight data from a CSV file
    vector<Freight> loadFreights(const string& path);

    // Load Cargo data from a CSV file
    vector<Cargo> loadCargos(const string& path);

    void saveSchedules(const ScheduleManager& manager, const string& path);
};
