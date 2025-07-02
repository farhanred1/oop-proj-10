// ScheduleManager.cpp
#include "ScheduleManager.h"
#include "FileManager.h"

ScheduleManager::ScheduleManager() {}

void ScheduleManager::generateSchedules(FreightManager& freightManager, CargoManager& cargoManager) {
    for (int i = 0; i < freightManager.getSize(); ++i) {
        Freight f = freightManager.getByIndex(i);
        bool matched = false;

        for (int j = 0; j < cargoManager.getSize(); ++j) {
            Cargo c = cargoManager.getByIndex(j);
            if (f.getCity() == c.getCity() && f.getTime() == c.getTime()) {
                scheduleList.push_back(Schedule(f, c));
                matched = true;
                break;  // One-to-one match
            }
        }

        if (!matched) {
            freightManager.addUnmatched(f);
        }
    }

    // Track unmatched cargos
    for (int j = 0; j < cargoManager.getSize(); ++j) {
        Cargo c = cargoManager.getByIndex(j);
        bool matched = false;

        for (const Schedule& s : scheduleList) {
            if (s.getCargo().getID() == c.getID()) {
                matched = true;
                break;
            }
        }

        if (!matched) {
            cargoManager.addUnmatched(c);
        }
    }
}

Schedule ScheduleManager::getByIndex(int index) const {
    return scheduleList.at(index);
}

int ScheduleManager::getSize() const {
    return scheduleList.size();
}

void ScheduleManager::exportToCSV(const std::string& path) const {
    std::vector<std::vector<std::string>> rows;
    rows.push_back({ "Freight ID", "City", "Time", "Cargo ID", "City", "Time" });

    for (const auto& schedule : scheduleList) {
        rows.push_back({
            schedule.getFreight().getID(),
            schedule.getFreight().getCity(),
            std::to_string(schedule.getFreight().getTime()),
            schedule.getCargo().getID(),
            schedule.getCargo().getCity(),
            std::to_string(schedule.getCargo().getTime())
            });
    }

    FileManager::saveCSV(path, rows);
}
