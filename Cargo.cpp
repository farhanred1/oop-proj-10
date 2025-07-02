// Cargo.cpp
#include "Cargo.h"
#include <iomanip>

// Constructor definition
Cargo::Cargo(const string& id, const string& city, int time)
    : TransportUnit(id, city, time) {
}

void Cargo::displayInfo() const {
    cout << "ID: " << getID()
        << ", City: " << getCity()
        << ", Time: " << setw(4) << setfill('0') << getTime() << endl;
}
