// Cargo.h
#pragma once
#include "TransportUnit.h"

class Cargo : public TransportUnit {
public:
    // Constructor declaration
    Cargo(const string& id, const string& city, int time);

    // Override displayInfo method
    void displayInfo() const override;
};
