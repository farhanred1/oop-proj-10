// Freight.h
#pragma once
#include "TransportUnit.h"
#include "Cargo.h"
#include <vector>

class Freight : public TransportUnit {
private:
    string type; // "MiniMover", "CargoCruiser", "MegaCarrier"
    vector<Cargo> assignedCargos;

public:
    // Constructor declaration
    Freight(const string& id, const string& city, int time, const string& type);

    // Override displayInfo method
    void displayInfo() const override;

    string getType() const;
    int getCapacity() const; // Converts type → capacity
    int getRemainingCapacity() const;

    int assignCargo(Cargo& cargo);
    const std::vector<Cargo>& getAssignedCargos() const;
    void clearAssignedCargos();

};