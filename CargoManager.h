// CargoManager.h
#pragma once
#include "RecordManager.h"
#include "Cargo.h"

class CargoManager : public RecordManager<Cargo> {
public:
    // Constructor
    CargoManager();
};