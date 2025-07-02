// Schedule.h
#pragma once
#include "Freight.h"
#include "Cargo.h"

class Schedule {
private:
    Freight freight;
    Cargo cargo;

public:
    // Constructor declaration
    Schedule(const Freight& f, const Cargo& c);

    // Setters
    void setFreight(const Freight& f);
    void setCargo(const Cargo& c);
    
    // Getters
    Freight getFreight() const;
    Cargo getCargo() const;

    // Display method
    void displaySchedule() const;
};
