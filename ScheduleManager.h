// ScheduleManager.h - Enhanced Version with Cargo Splitting Support
#pragma once

#include "Schedule.h"
#include "FreightManager.h"
#include "CargoManager.h"
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>

enum class SchedulingMode {
    TIME_PRIORITY,
    CAPACITY_OPTIMIZATION
};

class ScheduleManager {
private:
    std::vector<Schedule> scheduleList;
    std::vector<Freight> unmatchedFreights;
    std::vector<Cargo> unmatchedCargos;

    // Splitting statistics
    int totalSplitOperations;
    int totalCargosSplit;
    std::map<std::string, std::vector<std::string>> splitTracker; // Original ID -> Split IDs

    // Enhanced matching algorithms
    void matchFreightAndCargoTimePriority(FreightManager& freightManager, CargoManager& cargoManager);
    void matchFreightAndCargoCapacityOptimization(FreightManager& freightManager, CargoManager& cargoManager);

    // Time validation functions
    bool canDeliverOnTime(const Freight& freight, const Cargo& cargo) const;
    int calculateTimeDifference(int freightTime, int cargoTime) const;

    // Cargo splitting functions
    bool tryAssignCargoWithSplitting(const Cargo& cargo, std::vector<Freight>& availableFreights,
        std::vector<bool>& freightUsed);
    std::vector<int> calculateOptimalSplit(const Cargo& cargo, const std::vector<Freight>& availableFreights) const;
    bool canAccommodateSplitParts(const std::vector<int>& splitSizes, const std::vector<Freight>& freights) const;

    // Utility functions
    std::vector<Freight> getCompatibleFreights(const Cargo& cargo, const std::vector<Freight>& freights) const;
    void recordSplitOperation(const std::string& originalID, const std::vector<std::string>& splitIDs);

public:
    // Constructor
    ScheduleManager();

    // Enhanced schedule generation with mode selection
    void generateSchedules(FreightManager& freightManager, CargoManager& cargoManager,
        SchedulingMode mode = SchedulingMode::TIME_PRIORITY);

    // Get a schedule by its index
    Schedule getByIndex(int index) const;

    // Get total number of schedules
    int getSize() const;

    // Export all schedules to a CSV file with enhanced information
    void exportToCSV(const std::string& path) const;

    // Unmatched records handling
    const std::vector<Freight>& getUnmatchedFreights() const;
    const std::vector<Cargo>& getUnmatchedCargos() const;
    void displayUnmatchedFreights() const;
    void displayUnmatchedCargos() const;

    // Enhanced statistics and reporting
    void displaySchedulingStatistics() const;
    void displaySplittingStatistics() const;
    void displayDetailedStatistics() const;
};
