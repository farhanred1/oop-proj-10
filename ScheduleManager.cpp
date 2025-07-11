// ScheduleManager.cpp
#include "ScheduleManager.h"
#include "FileManager.h"

ScheduleManager::ScheduleManager() {}

void ScheduleManager::generateSchedules(FreightManager& freightManager, CargoManager& cargoManager) {
    // Clear previous results
    scheduleList.clear();
    unmatchedFreights.clear();
    unmatchedCargos.clear();

    matchFreightAndCargo(freightManager, cargoManager);
}

void ScheduleManager::matchFreightAndCargo(FreightManager& freightManager, CargoManager& cargoManager) {
    std::vector<bool> cargoMatched(cargoManager.getSize(), false);

    for (int i = 0; i < freightManager.getSize(); ++i) {
        Freight f = freightManager.getByIndex(i);
        bool matched = false;

        for (int j = 0; j < cargoManager.getSize(); ++j) {
            if (cargoMatched[j]) continue;

            Cargo c = cargoManager.getByIndex(j);

            if (f.getCity() == c.getCity() && f.getTime() == c.getTime()) {
                scheduleList.emplace_back(f, c);
                cargoMatched[j] = true;
                matched = true;
                break;  // one-to-one match
            }
        }

        if (!matched) {
            unmatchedFreights.push_back(f);
        }
    }

    // Any remaining unmatched cargo
    for (int j = 0; j < cargoManager.getSize(); ++j) {
        if (!cargoMatched[j]) {
            unmatchedCargos.push_back(cargoManager.getByIndex(j));
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