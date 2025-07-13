// Freight.cpp
#include "Freight.h"
#include <iomanip>

// Constructor definition
Freight::Freight(const string& id, const string& city, int time, const string& type)
    : TransportUnit(id, city, time), type(type) {
    // Additional Freight-specific initialization (if any)
}

// Override displayInfo method
void Freight::displayInfo() const {
    cout << "ID: " << getID()
        << ", City: " << getCity()
        << ", Time: " << setw(4) << setfill('0') << getTime() 
        << ", Type: " << type
        << ", Capacity: " << getCapacity()
        << ", Assigned: " << assignedCargos.size() << endl;
}

string Freight::getType() const { return type; }

int Freight::getCapacity() const {
    if (type == "MiniMover") return 2;
    if (type == "CargoCruiser") return 6;
    if (type == "MegaCarrier") return 12;
    throw invalid_argument("Unknown freight type: " + type);
}

int Freight::getRemainingCapacity() const {
    return getCapacity() - static_cast<int>(assignedCargos.size());
}

bool Freight::assignCargo(const Cargo& cargo) {
    if (getRemainingCapacity() >= cargo.getGroupSize()) {
        assignedCargos.push_back(cargo);
        return true;
    }
    return false; // Not enough capacity
}