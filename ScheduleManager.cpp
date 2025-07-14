// ScheduleManager.cpp - Enhanced Version with Cargo Splitting Support
#include "ScheduleManager.h"
#include "FileManager.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

ScheduleManager::ScheduleManager() : totalSplitOperations(0), totalCargosSplit(0) {}

void ScheduleManager::generateSchedules(FreightManager& freightManager, CargoManager& cargoManager, SchedulingMode mode) {
    // Clear previous results
    scheduleList.clear();
    unmatchedFreights.clear();
    unmatchedCargos.clear();
    totalSplitOperations = 0;
    totalCargosSplit = 0;
    splitTracker.clear();

    // Choose scheduling algorithm based on mode
    switch (mode) {
    case SchedulingMode::TIME_PRIORITY:
        matchFreightAndCargoTimePriority(freightManager, cargoManager);
        break;
    case SchedulingMode::CAPACITY_OPTIMIZATION:
        matchFreightAndCargoCapacityOptimization(freightManager, cargoManager);
        break;
    }

    cout << "\nScheduling completed using "
        << (mode == SchedulingMode::TIME_PRIORITY ? "TIME_PRIORITY" : "CAPACITY_OPTIMIZATION")
        << " mode.\n";
    displayDetailedStatistics();
}

void ScheduleManager::matchFreightAndCargoTimePriority(FreightManager& freightManager, CargoManager& cargoManager) {
    vector<bool> cargoMatched(cargoManager.getSize(), false);
    vector<bool> freightUsed(freightManager.getSize(), false);

    // Sort cargos by time (earliest first) for time priority
    vector<int> cargoIndices;
    for (int i = 0; i < cargoManager.getSize(); ++i) {
        cargoIndices.push_back(i);
    }

    sort(cargoIndices.begin(), cargoIndices.end(), [&](int a, int b) {
        return cargoManager.getByIndex(a).getTime() < cargoManager.getByIndex(b).getTime();
        });

    // Process each cargo in time order
    for (int cargoIdx : cargoIndices) {
        if (cargoMatched[cargoIdx]) continue;

        Cargo cargo = cargoManager.getByIndex(cargoIdx);
        bool assigned = false;

        // Try to assign to a single freight first
        for (int i = 0; i < freightManager.getSize(); ++i) {
            if (freightUsed[i]) continue;

            Freight freight = freightManager.getByIndex(i);

            if (canDeliverOnTime(freight, cargo) && freight.getRemainingCapacity() >= cargo.getGroupSize()) {
                freight.assignCargo(cargo);
                scheduleList.emplace_back(freight, cargo);
                cargoMatched[cargoIdx] = true;
                freightUsed[i] = true;
                assigned = true;
                break;
            }
        }

        // If not assigned, try splitting
        if (!assigned) {
            vector<Freight> availableFreights;
            vector<int> freightIndices;

            for (int i = 0; i < freightManager.getSize(); ++i) {
                if (!freightUsed[i]) {
                    Freight freight = freightManager.getByIndex(i);
                    if (canDeliverOnTime(freight, cargo) && freight.getRemainingCapacity() > 0) {
                        availableFreights.push_back(freight);
                        freightIndices.push_back(i);
                    }
                }
            }

            if (tryAssignCargoWithSplitting(cargo, availableFreights, freightUsed)) {
                cargoMatched[cargoIdx] = true;

                // Mark used freights
                for (size_t i = 0; i < availableFreights.size(); ++i) {
                    if (availableFreights[i].getRemainingCapacity() < availableFreights[i].getCapacity()) {
                        freightUsed[freightIndices[i]] = true;
                    }
                }
            }
        }
    }

    // Collect unmatched items
    for (int i = 0; i < freightManager.getSize(); ++i) {
        if (!freightUsed[i]) {
            unmatchedFreights.push_back(freightManager.getByIndex(i));
        }
    }

    for (int i = 0; i < cargoManager.getSize(); ++i) {
        if (!cargoMatched[i]) {
            unmatchedCargos.push_back(cargoManager.getByIndex(i));
        }
    }
}

void ScheduleManager::matchFreightAndCargoCapacityOptimization(FreightManager& freightManager, CargoManager& cargoManager) {
    vector<bool> cargoMatched(cargoManager.getSize(), false);
    vector<Freight> availableFreights;

    // Copy all freights and sort by capacity (largest first)
    for (int i = 0; i < freightManager.getSize(); ++i) {
        availableFreights.push_back(freightManager.getByIndex(i));
    }

    sort(availableFreights.begin(), availableFreights.end(), [](const Freight& a, const Freight& b) {
        return a.getCapacity() > b.getCapacity();
        });

    // Process each freight to maximize capacity utilization
    for (auto& freight : availableFreights) {
        bool freightUsed = false;

        // Try to fill this freight with compatible cargos
        for (int i = 0; i < cargoManager.getSize(); ++i) {
            if (cargoMatched[i]) continue;

            Cargo cargo = cargoManager.getByIndex(i);

            // Check if freight can accommodate whole cargo
            if (canDeliverOnTime(freight, cargo) && freight.getRemainingCapacity() >= cargo.getGroupSize()) {
                freight.assignCargo(cargo);
                scheduleList.emplace_back(freight, cargo);
                cargoMatched[i] = true;
                freightUsed = true;

                if (freight.getRemainingCapacity() == 0) {
                    break; // Freight is full
                }
            }
        }

        // If freight still has capacity, try to fill with split cargos
        if (freight.getRemainingCapacity() > 0) {
            for (int i = 0; i < cargoManager.getSize(); ++i) {
                if (cargoMatched[i]) continue;

                Cargo cargo = cargoManager.getByIndex(i);

                if (canDeliverOnTime(freight, cargo) && cargo.getGroupSize() > freight.getRemainingCapacity()) {
                    // Try to split this cargo
                    vector<Freight> singleFreight = { freight };
                    vector<bool> dummyUsed = { false };

                    if (tryAssignCargoWithSplitting(cargo, singleFreight, dummyUsed)) {
                        cargoMatched[i] = true;
                        freightUsed = true;
                        break;
                    }
                }
            }
        }
    }

    // Collect unmatched items
    for (const auto& freight : availableFreights) {
        if (freight.getRemainingCapacity() == freight.getCapacity()) {
            unmatchedFreights.push_back(freight);
        }
    }

    for (int i = 0; i < cargoManager.getSize(); ++i) {
        if (!cargoMatched[i]) {
            unmatchedCargos.push_back(cargoManager.getByIndex(i));
        }
    }
}

bool ScheduleManager::canDeliverOnTime(const Freight& freight, const Cargo& cargo) const {
    // Check if freight and cargo are in same city
    if (freight.getCity() != cargo.getCity()) {
        return false;
    }

    int timeDiff = calculateTimeDifference(freight.getTime(), cargo.getTime());

    // Freight can deliver if it arrives no more than 15 minutes early or exactly on time
    return timeDiff >= -15 && timeDiff <= 0;
}

int ScheduleManager::calculateTimeDifference(int freightTime, int cargoTime) const {
    // Convert HHMM format to minutes
    int freightMinutes = (freightTime / 100) * 60 + (freightTime % 100);
    int cargoMinutes = (cargoTime / 100) * 60 + (cargoTime % 100);

    // Return difference in minutes (negative means freight arrives early)
    return freightMinutes - cargoMinutes;
}

bool ScheduleManager::tryAssignCargoWithSplitting(const Cargo& cargo, vector<Freight>& availableFreights,
    vector<bool>& freightUsed) {
    // Calculate optimal split
    vector<int> splitSizes = calculateOptimalSplit(cargo, availableFreights);

    if (splitSizes.empty()) {
        return false; // Cannot split
    }

    // Create split parts
    vector<Cargo> splitParts = cargo.splitCargo(splitSizes);

    // Assign each split part to a freight
    for (size_t i = 0; i < splitParts.size(); ++i) {
        if (i < availableFreights.size()) {
            availableFreights[i].assignCargo(splitParts[i]);
            scheduleList.emplace_back(availableFreights[i], splitParts[i]);
        }
    }

    // Record splitting statistics
    totalSplitOperations++;
    totalCargosSplit++;

    vector<string> splitIDs;
    for (const auto& part : splitParts) {
        splitIDs.push_back(part.getID());
    }
    recordSplitOperation(cargo.getID(), splitIDs);

    return true;
}

vector<int> ScheduleManager::calculateOptimalSplit(const Cargo& cargo, const vector<Freight>& availableFreights) const {
    vector<int> splitSizes;
    int remainingSize = cargo.getGroupSize();

    // Get compatible freights and their capacities
    vector<Freight> compatibleFreights = getCompatibleFreights(cargo, availableFreights);

    if (compatibleFreights.empty()) {
        return splitSizes; // No compatible freights
    }

    // Sort by remaining capacity (largest first) for optimal packing
    sort(compatibleFreights.begin(), compatibleFreights.end(), [](const Freight& a, const Freight& b) {
        return a.getRemainingCapacity() > b.getRemainingCapacity();
        });

    // Greedy algorithm: assign as much as possible to each freight
    for (const auto& freight : compatibleFreights) {
        int assignable = min(remainingSize, freight.getRemainingCapacity());
        if (assignable > 0) {
            splitSizes.push_back(assignable);
            remainingSize -= assignable;

            if (remainingSize == 0) {
                break;
            }
        }
    }

    // Check if we can accommodate all cargo
    if (remainingSize > 0) {
        return vector<int>(); // Cannot accommodate all
    }

    return splitSizes;
}

vector<Freight> ScheduleManager::getCompatibleFreights(const Cargo& cargo, const vector<Freight>& freights) const {
    vector<Freight> compatible;

    for (const auto& freight : freights) {
        if (canDeliverOnTime(freight, cargo) && freight.getRemainingCapacity() > 0) {
            compatible.push_back(freight);
        }
    }

    return compatible;
}

void ScheduleManager::recordSplitOperation(const string& originalID, const vector<string>& splitIDs) {
    splitTracker[originalID] = splitIDs;
}

Schedule ScheduleManager::getByIndex(int index) const {
    return scheduleList.at(index);
}

int ScheduleManager::getSize() const {
    return scheduleList.size();
}

void ScheduleManager::exportToCSV(const string& path) const {
    vector<vector<string>> rows;
    rows.push_back({ "Freight ID", "Freight City", "Freight Time", "Freight Type", "Cargo ID",
                    "Cargo City", "Cargo Time", "Cargo Group Size", "Original Cargo ID",
                    "Split Part", "Time Difference (min)" });

    for (const auto& schedule : scheduleList) {
        int timeDiff = calculateTimeDifference(schedule.getFreight().getTime(), schedule.getCargo().getTime());

        string originalCargoID = schedule.getCargo().isSplitCargo() ?
            schedule.getCargo().getOriginalCargoID() :
            schedule.getCargo().getID();

        string splitInfo = schedule.getCargo().isSplitCargo() ?
            to_string(schedule.getCargo().getSplitPartNumber()) + "/" +
            to_string(schedule.getCargo().getTotalSplitParts()) :
            "No";

        rows.push_back({
            schedule.getFreight().getID(),
            schedule.getFreight().getCity(),
            to_string(schedule.getFreight().getTime()),
            schedule.getFreight().getType(),
            schedule.getCargo().getID(),
            schedule.getCargo().getCity(),
            to_string(schedule.getCargo().getTime()),
            to_string(schedule.getCargo().getGroupSize()),
            originalCargoID,
            splitInfo,
            to_string(timeDiff)
            });
    }

    FileManager::saveCSV(path, rows);
}

const vector<Freight>& ScheduleManager::getUnmatchedFreights() const {
    return unmatchedFreights;
}

const vector<Cargo>& ScheduleManager::getUnmatchedCargos() const {
    return unmatchedCargos;
}

void ScheduleManager::displayUnmatchedFreights() const {
    cout << "Unmatched Freights:\n";
    for (const auto& f : unmatchedFreights) {
        f.displayInfo();
    }
}

void ScheduleManager::displayUnmatchedCargos() const {
    cout << "Unmatched Cargos:\n";
    for (const auto& c : unmatchedCargos) {
        c.displayInfo();
    }
}

void ScheduleManager::displaySchedulingStatistics() const {
    cout << "\n=== Scheduling Statistics ===\n";
    cout << "Total Schedules Created: " << scheduleList.size() << "\n";
    cout << "Unmatched Freights: " << unmatchedFreights.size() << "\n";
    cout << "Unmatched Cargos: " << unmatchedCargos.size() << "\n";

    // Calculate capacity utilization
    int totalCapacityUsed = 0;
    int totalCapacityAvailable = 0;

    for (const auto& schedule : scheduleList) {
        totalCapacityUsed += schedule.getCargo().getGroupSize();
        totalCapacityAvailable += schedule.getFreight().getCapacity();
    }

    if (totalCapacityAvailable > 0) {
        double utilizationRate = (double)totalCapacityUsed / totalCapacityAvailable * 100;
        cout << "Capacity Utilization: " << fixed << setprecision(1) << utilizationRate << "%\n";
    }

    cout << "=============================\n";
}

void ScheduleManager::displaySplittingStatistics() const {
    cout << "\n=== Cargo Splitting Statistics ===\n";
    cout << "Total Split Operations: " << totalSplitOperations << "\n";
    cout << "Total Cargos Split: " << totalCargosSplit << "\n";

    if (!splitTracker.empty()) {
        cout << "\nSplit Details:\n";
        for (const auto& entry : splitTracker) {
            cout << "  " << entry.first << " -> ";
            for (size_t i = 0; i < entry.second.size(); ++i) {
                cout << entry.second[i];
                if (i < entry.second.size() - 1) cout << ", ";
            }
            cout << "\n";
        }
    }
    cout << "================================\n";
}

void ScheduleManager::displayDetailedStatistics() const {
    displaySchedulingStatistics();
    displaySplittingStatistics();
}
