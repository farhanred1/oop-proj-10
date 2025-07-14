// Schedule.cpp - Enhanced Version
#include "Schedule.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

// Constructor definitions
Schedule::Schedule(const Freight& f, const Cargo& c)
    : freight(f) {
    cargos.push_back(c);
}

Schedule::Schedule(const Freight& f, const std::vector<Cargo>& cargos)
    : freight(f), cargos(cargos) {}

// Setters
void Schedule::setFreight(const Freight& f) {
    freight = f;
}

void Schedule::setCargo(const Cargo& c) {
    cargos.clear();
    cargos.push_back(c);
}

void Schedule::setCargos(const std::vector<Cargo>& cargos) {
    this->cargos = cargos;
}

void Schedule::addCargo(const Cargo& c) {
    cargos.push_back(c);
}

// Getters
Freight Schedule::getFreight() const {
    return freight;
}

Cargo Schedule::getCargo() const {
    if (cargos.empty()) {
        throw runtime_error("No cargo in schedule");
    }
    return cargos[0]; // Return first cargo for backward compatibility
}

const std::vector<Cargo>& Schedule::getCargos() const {
    return cargos;
}

// Enhanced display methods
void Schedule::displaySchedule() const {
    cout << "\n=== Schedule ===\n";
    cout << "Freight: ";
    freight.displayInfo();

    cout << "Cargo(s): \n";
    for (size_t i = 0; i < cargos.size(); ++i) {
        cout << "  " << (i + 1) << ". ";
        cargos[i].displayInfo();
    }

    cout << "Capacity Utilization: " << fixed << setprecision(1)
        << getCapacityUtilization() << "%\n";
    cout << "===============\n";
}

void Schedule::displayDetailedSchedule() const {
    cout << "\n=== Detailed Schedule ===\n";
    freight.displayDetailedInfo();

    cout << "\nCargo Details:\n";
    for (size_t i = 0; i < cargos.size(); ++i) {
        cout << "Cargo " << (i + 1) << ":\n";
        cout << "  ID: " << cargos[i].getID() << "\n";
        cout << "  City: " << cargos[i].getCity() << "\n";
        cout << "  Time: " << setw(4) << setfill('0') << cargos[i].getTime() << "\n";
        cout << "  Group Size: " << cargos[i].getGroupSize() << "\n";
        cout << "\n";
    }

    cout << "Total Cargo Size: " << getTotalCargoSize() << "\n";
    cout << "Freight Capacity: " << freight.getCapacity() << "\n";
    cout << "Remaining Capacity: " << (freight.getCapacity() - getTotalCargoSize()) << "\n";
    cout << "Utilization: " << fixed << setprecision(1) << getCapacityUtilization() << "%\n";
    cout << "========================\n";
}

void Schedule::displayScheduleWithTiming() const {
    cout << "\n=== Schedule with Timing Analysis ===\n";
    freight.displayInfo();

    cout << "Cargo Deliveries:\n";
    for (size_t i = 0; i < cargos.size(); ++i) {
        cout << "  " << (i + 1) << ". ";
        cargos[i].displayInfo();

        // Calculate time difference
        int freightMinutes = (freight.getTime() / 100) * 60 + (freight.getTime() % 100);
        int cargoMinutes = (cargos[i].getTime() / 100) * 60 + (cargos[i].getTime() % 100);
        int timeDiff = freightMinutes - cargoMinutes;

        cout << "     Time Difference: " << timeDiff << " minutes ";
        if (timeDiff < 0) {
            cout << "(Early delivery)";
        }
        else if (timeDiff == 0) {
            cout << "(On-time delivery)";
        }
        else {
            cout << "(Late delivery)";
        }
        cout << "\n";
    }

    cout << "Capacity: " << getTotalCargoSize() << "/" << freight.getCapacity()
        << " (" << fixed << setprecision(1) << getCapacityUtilization() << "%)\n";
    cout << "=================================\n";
}

// Validation methods
bool Schedule::isValidSchedule() const {
    if (cargos.empty()) {
        return false;
    }

    // Check if all cargos are in the same city as freight
    for (const auto& cargo : cargos) {
        if (cargo.getCity() != freight.getCity()) {
            return false;
        }
    }

    // Check if freight has enough capacity
    return canAccommodateAllCargos();
}

bool Schedule::canAccommodateAllCargos() const {
    return getTotalCargoSize() <= freight.getCapacity();
}

// Utility methods
int Schedule::getTotalCargoSize() const {
    int total = 0;
    for (const auto& cargo : cargos) {
        total += cargo.getGroupSize();
    }
    return total;
}

double Schedule::getCapacityUtilization() const {
    if (freight.getCapacity() == 0) {
        return 0.0;
    }
    return (double)getTotalCargoSize() / freight.getCapacity() * 100.0;
}
