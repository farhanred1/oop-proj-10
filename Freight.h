// Freight.h
#pragma once
#include "TransportUnit.h"

class Freight : public TransportUnit {
public:
    // Constructor declaration
    Freight(const string& id, const string& city, int time);

    // Override displayInfo method
    void displayInfo() const override;
};
