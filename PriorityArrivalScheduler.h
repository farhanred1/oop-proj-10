// PriorityArrivalScheduler.h
#pragma once
#include "Scheduler.h"
class PriorityArrivalScheduler : public Scheduler
{
public:
    void generateSchedules(
        FreightManager& freightMgr,
        CargoManager& cargoMgr,
        ScheduleManager& scheduleMgr) override;
};

// Author: Farhan