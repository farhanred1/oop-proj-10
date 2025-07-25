// ScheduleManager.cpp
// Author: Muhammad Rais Bin Sani
#include "ScheduleManager.h"
#include "FileManager.h"
#include "Scheduler.h"
#include "Schedule.h"
#include "FreightManager.h"
#include "CargoManager.h"

ScheduleManager::ScheduleManager() : scheduler(nullptr) {}

void ScheduleManager::setScheduler(Scheduler* s) {
    scheduler = s;
}

void ScheduleManager::generateSchedules(FreightManager& freightManager, CargoManager& cargoManager) {
    // Clear previous results
    scheduleList.clear();
    unmatchedFreights.clear();
    unmatchedCargos.clear();

    // Reset freights & cargos if needed (e.g., clear assigned cargos)
    for (Freight& f : freightManager) f.clearAssignedCargos();
    for (Cargo& c : cargoManager) c.setGroupSize(c.getGroupSize()); // ensures correct groupSize

    if (scheduler) {
        scheduler->generateSchedules(freightManager, cargoManager, *this);
    }
}

// Add schedule
void ScheduleManager::addSchedule(const Schedule& schedule) {
    scheduleList.push_back(schedule);
}

// Track unmatched freight
void ScheduleManager::addUnmatchedFreight(const Freight& freight) {
    unmatchedFreights.push_back(freight);
}

// Track unmatched cargo
void ScheduleManager::addUnmatchedCargo(const Cargo& cargo) {
    unmatchedCargos.push_back(cargo);
}

Schedule ScheduleManager::getByIndex(int index) const {
    return scheduleList.at(index);
}

int ScheduleManager::getSize() const {
    return scheduleList.size();
}

void ScheduleManager::exportToCSV(const std::string& path) const {
    std::vector<std::vector<std::string>> rows;
    rows.push_back({ "Freight ID", "City", "Time", "Type", "Cargo ID", "Cargo City", "Cargo Time", "Cargo GroupSize" });

    for (const auto& schedule : scheduleList) {
        const Freight& freight = schedule.getFreight();
        const auto& cargos = schedule.getCargos();

        if (cargos.empty()) {
            rows.push_back({
                freight.getID(), freight.getCity(), std::to_string(freight.getTime()), freight.getType(),
                "-", "-", "-", "-"
                });
        }
        else {
            for (const Cargo& cargo : cargos) {
                rows.push_back({
                    freight.getID(), freight.getCity(), std::to_string(freight.getTime()), freight.getType(),
                    cargo.getID(), cargo.getCity(), std::to_string(cargo.getTime()), std::to_string(cargo.getGroupSize())
                    });
            }
        }
    }

    FileManager::saveCSV(path, rows);
}

const std::vector<Freight>& ScheduleManager::getUnmatchedFreights() const {
    return unmatchedFreights;
}

const std::vector<Cargo>& ScheduleManager::getUnmatchedCargos() const {
    return unmatchedCargos;
}

void ScheduleManager::displayUnmatchedFreights() const {
    std::cout << "Unmatched Freights:\n";
    for (const auto& f : unmatchedFreights) {
        f.displayInfo();
    }
}

void ScheduleManager::displayUnmatchedCargos() const {
    std::cout << "Unmatched Cargos:\n";
    for (const auto& c : unmatchedCargos) {
        c.displayInfo();
    }
}
void ScheduleManager::displaySchedules() const {
    std::cout << "\nSchedules:\n";
    for (const auto& s : scheduleList) {
        s.displaySchedule();
    }
}
// Author: Muhammad Rais Bin Sani


// Author: Farhan
int ScheduleManager::calculateTimeDifference(int freightTime, int cargoTime) const {
    // Convert HHMM format to minutes
    int freightMinutes = (freightTime / 100) * 60 + (freightTime % 100);
    int cargoMinutes = (cargoTime / 100) * 60 + (cargoTime % 100);

    // Return difference in minutes (negative means freight arrives early)
    return freightMinutes - cargoMinutes;
}