// Cargo.h - Enhanced Version with Cargo Splitting Support
#pragma once

#include "TransportUnit.h"
#include <vector>
#include <string>

class Cargo : public TransportUnit {
private:
    int groupSize;
    int originalGroupSize;        // Track original size for split cargo
    std::string originalCargoID;  // Track original cargo ID for split parts
    int splitPartNumber;          // Track which part of the split this is
    int totalSplitParts;          // Track total number of split parts
    bool isSplit;                 // Flag to indicate if this is a split cargo

public:
    // Constructor declarations
    Cargo(const std::string& id, const std::string& city, int time, int groupSize = 1);

    // Split cargo constructor (for creating split parts)
    Cargo(const std::string& id, const std::string& city, int time, int groupSize,
        const std::string& originalCargoID, int originalGroupSize,
        int splitPartNumber, int totalSplitParts);

    // Override displayInfo method
    void displayInfo() const override;

    // Getter and setter for groupSize
    int getGroupSize() const;
    void setGroupSize(int size);

    // Split cargo functionality
    std::vector<Cargo> splitCargo(const std::vector<int>& splitSizes) const;

    // Split cargo information methods
    bool isSplitCargo() const;
    std::string getOriginalCargoID() const;
    int getOriginalGroupSize() const;
    int getSplitPartNumber() const;
    int getTotalSplitParts() const;

    // Display methods for split cargo
    void displaySplitInfo() const;
    void displayDetailedInfo() const;
};
