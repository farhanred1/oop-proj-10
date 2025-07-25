// MinFreightScheduler.h
// Author: Myat Htun
#pragma once
#include "Scheduler.h"
class MinFreightScheduler : public Scheduler
{
public:
    void generateSchedules(
        FreightManager& freightMgr,
        CargoManager& cargoMgr,
        ScheduleManager& scheduleMgr) override;
};

