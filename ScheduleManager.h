// ScheduleManager.h
#pragma once
#include "Schedule.h"
#include "FreightManager.h"
#include "CargoManager.h"

class ScheduleManager {
private:
    vector<Schedule> scheduleList;

public:
    // Constructor declaration
    ScheduleManager();

    // Generate and manage schedules
    void generateSchedules(FreightManager& freightManager, CargoManager& cargoManager);
    Schedule getByIndex(int index) const;
    int getSize() const;
};
