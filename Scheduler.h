// Scheduler.h
#pragma once
#include "FreightManager.h"
#include "CargoManager.h"
class ScheduleManager;  // forward declaration

class Scheduler {
public:
    virtual ~Scheduler() {}
    virtual void generateSchedules(
        FreightManager& freightMgr,
        CargoManager& cargoMgr,
        ScheduleManager& scheduleMgr) = 0;
};
