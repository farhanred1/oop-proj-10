// Freight.cpp
#include "Freight.h"
#include <iomanip>

// Constructor definition
Freight::Freight(const string& id, const string& city, int time)
    : TransportUnit(id, city, time) {
    // Additional Freight-specific initialization (if any)
}

// Override displayInfo method
void Freight::displayInfo() const {
    cout << "ID: " << getID()
        << ", City: " << getCity()
        << ", Time: " << setw(4) << setfill('0') << getTime() << endl;
}