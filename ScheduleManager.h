// ScheduleManager.h
#pragma once
#include "Schedule.h"
#include "FreightManager.h"
#include "CargoManager.h"

class ScheduleManager {
private:
    vector<Schedule> scheduleList;

public:
    // Constructor
    ScheduleManager();

    // Generate schedules by matching freight and cargo
    void generateSchedules(FreightManager& freightManager, CargoManager& cargoManager);

    // Get a schedule by its index
    Schedule getByIndex(int index) const;

    // Get total number of schedules
    int getSize() const;

    // Export all schedules to a CSV file
    void exportToCSV(const std::string& path) const;
};
