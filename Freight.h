// Freight.h - Enhanced Version
#pragma once

#include "TransportUnit.h"
#include "Cargo.h"
#include <vector>
#include <string>

class Freight : public TransportUnit {
private:
    std::string type; // "MiniMover", "CargoCruiser", "MegaCarrier"
    std::vector<Cargo> assignedCargos; // Support for multiple cargos

public:
    // Constructor declaration
    Freight(const std::string& id, const std::string& city, int time, const std::string& type);

    // Override displayInfo method
    void displayInfo() const override;

    // Type and capacity methods
    std::string getType() const;
    int getCapacity() const; // Converts type to capacity
    int getRemainingCapacity() const;
    int getUsedCapacity() const;

    // Cargo assignment methods
    bool assignCargo(const Cargo& cargo);
    void clearAssignedCargos();
    const std::vector<Cargo>& getAssignedCargos() const;

    // Enhanced display methods
    void displayDetailedInfo() const;
    void displayCapacityInfo() const;
};
    