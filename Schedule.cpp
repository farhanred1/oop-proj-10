// Schedule.cpp
#include "Schedule.h"

// Constructor definition
Schedule::Schedule(const Freight& f, const Cargo& c)
    : freight(f), cargo(c) {}

// Setters
void Schedule::setFreight(const Freight& f) {
    freight = f;
}

void Schedule::setCargo(const Cargo& c) {
    cargo = c;
}

// Getters
Freight Schedule::getFreight() const {
    return freight;
}

Cargo Schedule::getCargo() const {
    return cargo;
}

// Display
void Schedule::displaySchedule() const {
    // Display freight details
    cout << "  Freight: ";
    freight.displayInfo();

    // Display cargo details
    cout << "  Cargo: ";
    cargo.displayInfo();
}
