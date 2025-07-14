// Freight.cpp - Enhanced Version
#include "Freight.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// Constructor definition
Freight::Freight(const string& id, const string& city, int time, const string& type)
    : TransportUnit(id, city, time), type(type) {
    // Validate freight type
    if (type != "MiniMover" && type != "CargoCruiser" && type != "MegaCarrier") {
        throw invalid_argument("Invalid freight type: " + type);
    }
}

// Override displayInfo method
void Freight::displayInfo() const {
    cout << "ID: " << getID()
        << ", City: " << getCity()
        << ", Time: " << setw(4) << setfill('0') << getTime()
        << ", Type: " << type
        << ", Capacity: " << getUsedCapacity() << "/" << getCapacity();

    if (!assignedCargos.empty()) {
        cout << " [Assigned: " << assignedCargos.size() << " cargo(s)]";
    }
    cout << endl;
}

void Freight::displayDetailedInfo() const {
    cout << "\n=== Freight Details ===\n";
    cout << "ID: " << getID() << "\n";
    cout << "City: " << getCity() << "\n";
    cout << "Time: " << setw(4) << setfill('0') << getTime() << "\n";
    cout << "Type: " << type << "\n";
    cout << "Capacity: " << getUsedCapacity() << "/" << getCapacity() << "\n";

    if (!assignedCargos.empty()) {
        cout << "\nAssigned Cargos:\n";
        for (size_t i = 0; i < assignedCargos.size(); ++i) {
            cout << "  " << (i + 1) << ". ";
            assignedCargos[i].displayInfo();
        }
    }
    else {
        cout << "No assigned cargos.\n";
    }
    cout << "=====================\n";
}

void Freight::displayCapacityInfo() const {
    cout << "Capacity: " << getUsedCapacity() << "/" << getCapacity()
        << " (Remaining: " << getRemainingCapacity() << ")\n";
}

string Freight::getType() const {
    return type;
}

int Freight::getCapacity() const {
    if (type == "MiniMover") return 2;
    if (type == "CargoCruiser") return 6;
    if (type == "MegaCarrier") return 12;
    throw invalid_argument("Unknown freight type: " + type);
}

int Freight::getUsedCapacity() const {
    int used = 0;
    for (const auto& cargo : assignedCargos) {
        used += cargo.getGroupSize();
    }
    return used;
}

int Freight::getRemainingCapacity() const {
    return getCapacity() - getUsedCapacity();
}

bool Freight::assignCargo(const Cargo& cargo) {
    if (getRemainingCapacity() >= cargo.getGroupSize()) {
        assignedCargos.push_back(cargo);
        return true;
    }
    return false; // Not enough capacity
}

void Freight::clearAssignedCargos() {
    assignedCargos.clear();
}

const vector<Cargo>& Freight::getAssignedCargos() const {
    return assignedCargos;
}
    