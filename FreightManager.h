// FreightManager.h
// Author: Alastair Gillyson Lamiao Madrid
#pragma once
#include "RecordManager.h"
#include "Freight.h"

class FreightManager : public RecordManager<Freight> {
public:
    // Constructor
    FreightManager();

    // Load Freight records from CSV file
    void loadFromCSV(const std::string& path);
};
