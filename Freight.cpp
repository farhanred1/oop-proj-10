// Freight.cpp
// Author: Farhan Reduan Ahammed
#include "Freight.h"
#include <iomanip>

// Constructor definition
Freight::Freight(const string& id, const string& city, int time, const string& type)
    : TransportUnit(id, city, time), type(type) {
}

// Display Info
void Freight::displayInfo() const {
    int totalAssigned = 0;
    for (const Cargo& c : assignedCargos) {
        totalAssigned += c.getGroupSize();
    }

    cout << "ID: " << getID()
        << ", City: " << getCity()
        << ", Time: " << setw(4) << setfill('0') << getTime()
        << ", Type: " << type
        << ", Capacity: " << getCapacity()
        << ", Assigned Units: " << totalAssigned << endl;

    if (!assignedCargos.empty()) {
        cout << "  Assigned Cargos:" << endl;
        for (const Cargo& c : assignedCargos) {
            cout << "    ID: " << c.getID()
                << ", City: " << c.getCity()
                << ", Time: " << c.getTime()
                << ", Units Assigned: " << c.getGroupSize() << endl;
        }
    }
}

string Freight::getType() const { return type; }

int Freight::getCapacity() const {
    if (type == "MiniMover") return 2;
    if (type == "CargoCruiser") return 6;
    if (type == "MegaCarrier") return 12;
    throw invalid_argument("Unknown freight type: " + type);
}

int Freight::getRemainingCapacity() const {
    int used = 0;
    for (const Cargo& c : assignedCargos) {
        used += c.getGroupSize();
    }
    return getCapacity() - used;
}

int Freight::assignCargo(Cargo& cargo) {
    int available = getRemainingCapacity();
    int needed = cargo.getGroupSize();
    int assigned = std::min(available, needed);

    if (assigned <= 0) {
        /*std::cout << "[DEBUG] Freight " << getID() << " has no capacity left.\n";*/
        return 0;
    }

    // Create a copy of the cargo with only the assigned units
    Cargo assignedCargo = cargo;
    assignedCargo.setGroupSize(assigned);

    assignedCargos.push_back(assignedCargo);

    cargo.setGroupSize(needed - assigned);

    /*std::cout << "[DEBUG] Assigned " << assigned
        << " units of Cargo " << cargo.getID()
        << " to Freight " << getID()
        << ". Remaining capacity: " << getRemainingCapacity()
        << ", Cargo remaining: " << cargo.getGroupSize() << "\n";*/

    return assigned;
}

const std::vector<Cargo>& Freight::getAssignedCargos() const {
    return assignedCargos;
}
void Freight::clearAssignedCargos() {
    assignedCargos.clear();
}

// Author: Farhan Reduan Ahammed