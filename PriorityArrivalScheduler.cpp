// PriorityArrivalScheduler.cpp
#include "PriorityArrivalScheduler.h"
#include "Schedule.h"
#include "ScheduleManager.h"
#include "Freight.h"
#include <iostream>
#include <algorithm>

// TO DO
// Refactor logic to allow cargo with earlier time to be in first
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// Checks if the freight is eligible to carry this cargo
static bool canAssign(Freight& freight, Cargo& cargo, ScheduleManager& scheduleMgr) {
    const int EARLY_LIMIT = 15;

    if (freight.getCity() != cargo.getCity()) {
        std::cout << "    [SKIP] Destination mismatch.\n";
        return false;
    }

    int timeDiff = scheduleMgr.calculateTimeDifference(freight.getTime(), cargo.getTime());

    if (timeDiff > 0 || timeDiff < -EARLY_LIMIT) {
        std::cout << "    [SKIP] Time constraint violated (difference: " << timeDiff << " minutes).\n";
        return false;
    }

    if (freight.getRemainingCapacity() <= 0) {
        std::cout << "    [SKIP] No remaining capacity.\n";
        return false;
    }

    return true;
}

void PriorityArrivalScheduler::generateSchedules(
    FreightManager& freightMgr,
    CargoManager& cargoMgr,
    ScheduleManager& scheduleMgr)
{
    std::cout << "[INFO] Starting Priority Arrival Scheduler\n";

    for (Cargo& cargo : cargoMgr) {
        std::cout << "[INFO] Scheduling Cargo: " << cargo.getID()
            << " (Group Size: " << cargo.getGroupSize()
            << "), Destination: " << cargo.getCity()
            << ", Time: " << cargo.getTime() << "\n";

        for (Freight& freight : freightMgr) {
            std::cout << "  [CHECK] Freight: " << freight.getID()
                << ", Destination: " << freight.getCity()
                << ", Time: " << freight.getTime()
                << ", Remaining Capacity: " << freight.getRemainingCapacity() << "\n";

            if (!canAssign(freight, cargo, scheduleMgr))
                continue;

            int assigned = freight.assignCargo(cargo);

            if (assigned > 0) {
                if (cargo.getGroupSize() == 0) {
                    std::cout << "    [DONE] Cargo fully assigned.\n";
                    break; // stop checking freights for this cargo
                }
                else {
                    std::cout << "    [CONTINUE] Remaining Cargo units: "
                        << cargo.getGroupSize() << "\n";
                }
            }
        }

        if (cargo.getGroupSize() > 0) {
            std::cout << "[WARNING] Cargo group " << cargo.getID()
                << " (" << cargo.getGroupSize()
                << " units remaining) could not be fully scheduled.\n";
            scheduleMgr.addUnmatchedCargo(cargo);
        }
    }

    // Create schedules for freights
    for (Freight& freight : freightMgr) {
        if (!freight.getAssignedCargos().empty()) {
            Schedule schedule(freight, freight.getAssignedCargos());
            scheduleMgr.addSchedule(schedule);
        }
        else {
            scheduleMgr.addUnmatchedFreight(freight);
        }
    }

    std::cout << "[INFO] Scheduling complete.\n";
}