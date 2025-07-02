// FreightManager.h
#pragma once
#include "RecordManager.h"
#include "Freight.h"

class FreightManager : public RecordManager<Freight> {
public:
    // Constructor
    FreightManager();
};
