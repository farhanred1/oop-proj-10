// Schedule.cpp
#include "Schedule.h"
// Author: Muhammad Rais Bin Sani
// 
// Constructor definition
Schedule::Schedule(const Freight& f, const std::vector<Cargo>& c)
    : freight(f), cargos(c) {}


// Setters
void Schedule::setFreight(const Freight& f) {
    freight = f;
}

void Schedule::setCargos(const std::vector<Cargo>& c) {
    cargos = c;
}

// Getters
Freight Schedule::getFreight() const {
    return freight;
}

std::vector<Cargo> Schedule::getCargos() const {
    return cargos;
}

// Display
void Schedule::displaySchedule() const {
    // Display freight details
    cout << "\nFreight: "; 
    freight.displayInfo();

    // Display all assigned cargos
    if (cargos.empty()) {
        cout << "  No cargos assigned to this freight.\n";
    }
    //else {
    //    cout << "  Assigned Cargos:\n";
    //    for (const Cargo& cargo : cargos) {
    //        cout << "    ";
    //        cargo.displayInfo();
    //    }
    //}

    cout << "---------------------------------------\n";
}
// Author: Muhammad Rais Bin Sani