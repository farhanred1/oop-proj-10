// ScheduleManager.h
// Author: Muhammad Rais Bin Sani
#pragma once
#include "Schedule.h"
#include "FreightManager.h"
#include "CargoManager.h"
#include "Scheduler.h"

class ScheduleManager {
private:
    vector<Schedule> scheduleList;
    vector<Freight> unmatchedFreights;
    vector<Cargo> unmatchedCargos;
    Scheduler* scheduler;  // pointer to current strategy

public:
    // Constructor
    ScheduleManager();

    void setScheduler(Scheduler* s);

    void generateSchedules(FreightManager& freightManager, CargoManager& cargoManager);

    void addSchedule(const Schedule& schedule);
    void addUnmatchedFreight(const Freight& freight);
    void addUnmatchedCargo(const Cargo& cargo);

    // Get a schedule by its index
    Schedule getByIndex(int index) const;

    // Get total number of schedules
    int getSize() const;

    // Export all schedules to a CSV file
    void exportToCSV(const std::string& path) const;

    int calculateTimeDifference(int freightTime, int cargoTime) const;

    // NEED TO CHECK
    const std::vector<Freight>& getUnmatchedFreights() const;
    const std::vector<Cargo>& getUnmatchedCargos() const;
    void displayUnmatchedFreights() const;
    void displayUnmatchedCargos() const;
    void displaySchedules() const;
};
