// Schedule.h - Enhanced Version
#pragma once

#include "Freight.h"
#include "Cargo.h"
#include <vector>

class Schedule {
private:
    Freight freight;
    std::vector<Cargo> cargos; // Support for multiple cargos per freight

public:
    // Constructor declarations
    Schedule(const Freight& f, const Cargo& c);
    Schedule(const Freight& f, const std::vector<Cargo>& cargos);

    // Setters
    void setFreight(const Freight& f);
    void setCargo(const Cargo& c);
    void setCargos(const std::vector<Cargo>& cargos);
    void addCargo(const Cargo& c);

    // Getters
    Freight getFreight() const;
    Cargo getCargo() const; // Returns first cargo for backward compatibility
    const std::vector<Cargo>& getCargos() const;

    // Enhanced display methods
    void displaySchedule() const;
    void displayDetailedSchedule() const;
    void displayScheduleWithTiming() const;

    // Validation methods
    bool isValidSchedule() const;
    bool canAccommodateAllCargos() const;

    // Utility methods
    int getTotalCargoSize() const;
    double getCapacityUtilization() const;
};
