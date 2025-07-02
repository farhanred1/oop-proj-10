// IDataParser.h
#pragma once
#include "Freight.h"
#include "Cargo.h"
#include <vector>
#include <string>

class IDataParser {
public:
    // Pure virtual functions for loading data
    virtual vector<Freight> loadFreights(const string& path) = 0;
    virtual vector<Cargo> loadCargos(const string& path) = 0;

    virtual ~IDataParser() = default; // Virtual destructor
};
