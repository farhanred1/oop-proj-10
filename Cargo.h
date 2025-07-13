// Cargo.h
#pragma once
#include "TransportUnit.h"

class Cargo : public TransportUnit {
private:
    int groupSize;

public:
    // Constructor declaration
    Cargo(const string& id, const string& city, int time, int groupSize = 1);

    // Override displayInfo method
    void displayInfo() const override;

	// Getter and setter for groupSize
    int getGroupSize() const;
    void setGroupSize(int size);
};
