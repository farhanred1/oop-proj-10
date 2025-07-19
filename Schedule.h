// Schedule.h
#pragma once
#include "Freight.h"
#include "Cargo.h"

class Schedule {
private:
    Freight freight;
    std::vector<Cargo> cargos;

public:
    // Constructor declaration
    Schedule(const Freight& f, const std::vector<Cargo>& c);

    // Setters
    void setFreight(const Freight& f);
    void setCargos(const std::vector<Cargo>& c);
    
    // Getters
    Freight getFreight() const;
    std::vector<Cargo> getCargos() const;

    // Display method
    void displaySchedule() const;
};
