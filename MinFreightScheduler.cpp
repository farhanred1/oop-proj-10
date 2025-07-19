// MinFreightScheduler.cpp
#include "MinFreightScheduler.h"
#include "Schedule.h"
#include "ScheduleManager.h"
#include <iostream>
#include <algorithm>

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

void MinFreightScheduler::generateSchedules(
    FreightManager& freightMgr,
    CargoManager& cargoMgr,
    ScheduleManager& scheduleMgr)
{
    std::cout << "\n[INFO] Starting Minimum Freight Scheduler\n";

    // Step 1: Collect & sort freights largest → smallest
    std::vector<Freight*> freights;
    for (Freight& f : freightMgr) {
        freights.push_back(&f);
    }

    std::sort(freights.begin(), freights.end(),
        [](const Freight* a, const Freight* b) {
            return a->getCapacity() > b->getCapacity();
        });

    std::cout << "[DEBUG] Freights sorted by capacity:\n";
    for (const auto* f : freights) {
        std::cout << "  Freight " << f->getID() << " (" << f->getType()
            << ") Capacity: " << f->getCapacity() << "\n";
    }

    // Step 2: Assign cargos
    for (Freight* freight : freights) {
        bool freightUsed = false;

        std::cout << "\n[INFO] Processing Freight: " << freight->getID()
            << ", Remaining Capacity: " << freight->getRemainingCapacity() << "\n";

        for (Cargo& cargo : cargoMgr) {
            if (cargo.getGroupSize() <= 0) continue;

            std::cout << "[CHECK] Cargo: " << cargo.getID()
                << ", Group Size: " << cargo.getGroupSize()
                << ", Destination: " << cargo.getCity()
                << ", Time: " << cargo.getTime() << "\n";

            if (!canAssign(*freight, cargo, scheduleMgr)) {
                continue;
            }

            int assigned = freight->assignCargo(cargo);

            if (assigned > 0) {
                std::cout << "  [ASSIGN] Assigned " << assigned << " units of Cargo "
                    << cargo.getID() << " → Freight " << freight->getID() << "\n";

                freightUsed = true;

                if (freight->getRemainingCapacity() == 0) {
                    std::cout << "  [FULL] Freight fully loaded.\n";
                    break;
                }
            }
        }

        if (freightUsed) {
            scheduleMgr.addSchedule(Schedule(*freight, freight->getAssignedCargos()));
        }
        else {
            scheduleMgr.addUnmatchedFreight(*freight);
        }
    }

    // Step 3: Remaining unmatched cargos
    for (Cargo& cargo : cargoMgr) {
        if (cargo.getGroupSize() > 0) {
            std::cout << "[WARNING] Cargo " << cargo.getID() << " has "
                << cargo.getGroupSize() << " units unassigned.\n";
            scheduleMgr.addUnmatchedCargo(cargo);
        }
    }

    std::cout << "\n[INFO] Minimum Freight Scheduling complete.\n";
}