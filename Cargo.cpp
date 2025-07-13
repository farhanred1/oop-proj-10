// Cargo.cpp
#include "Cargo.h"
#include <iomanip>

// Constructor definition
Cargo::Cargo(const string& id, const string& city, int time, int groupSize)
    : TransportUnit(id, city, time), groupSize(groupSize) {
}

void Cargo::displayInfo() const {
    cout << "ID: " << getID()
        << ", City: " << getCity()
        << ", Time: " << setw(4) << setfill('0') << getTime()
        << ", Group Size: " << groupSize << endl;
}

int Cargo::getGroupSize() const { return groupSize; }
void Cargo::setGroupSize(int size) { groupSize = size; }