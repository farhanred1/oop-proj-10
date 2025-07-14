// Cargo.cpp - Enhanced Version with Cargo Splitting Support
#include "Cargo.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

// Constructor definition
Cargo::Cargo(const string& id, const string& city, int time, int groupSize)
    : TransportUnit(id, city, time), groupSize(groupSize), originalGroupSize(groupSize),
    originalCargoID(id), splitPartNumber(1), totalSplitParts(1), isSplit(false) {
}

// Split cargo constructor
Cargo::Cargo(const string& id, const string& city, int time, int groupSize,
    const string& originalCargoID, int originalGroupSize,
    int splitPartNumber, int totalSplitParts)
    : TransportUnit(id, city, time), groupSize(groupSize), originalGroupSize(originalGroupSize),
    originalCargoID(originalCargoID), splitPartNumber(splitPartNumber),
    totalSplitParts(totalSplitParts), isSplit(true) {
}

void Cargo::displayInfo() const {
    cout << "ID: " << getID()
        << ", City: " << getCity()
        << ", Time: " << setw(4) << setfill('0') << getTime()
        << ", Group Size: " << groupSize;

    if (isSplit) {
        cout << " [Split " << splitPartNumber << "/" << totalSplitParts
            << " of " << originalCargoID << "]";
    }
    cout << endl;
}

void Cargo::displaySplitInfo() const {
    if (isSplit) {
        cout << "Split Cargo Details:\n";
        cout << "  Original Cargo ID: " << originalCargoID << "\n";
        cout << "  Original Group Size: " << originalGroupSize << "\n";
        cout << "  Split Part: " << splitPartNumber << "/" << totalSplitParts << "\n";
        cout << "  This Part Size: " << groupSize << "\n";
    }
    else {
        cout << "This cargo is not split.\n";
    }
}

void Cargo::displayDetailedInfo() const {
    cout << "\n=== Cargo Details ===\n";
    cout << "ID: " << getID() << "\n";
    cout << "City: " << getCity() << "\n";
    cout << "Time: " << setw(4) << setfill('0') << getTime() << "\n";
    cout << "Group Size: " << groupSize << "\n";

    if (isSplit) {
        cout << "Original Cargo ID: " << originalCargoID << "\n";
        cout << "Original Group Size: " << originalGroupSize << "\n";
        cout << "Split Part: " << splitPartNumber << "/" << totalSplitParts << "\n";
    }
    cout << "====================\n";
}

int Cargo::getGroupSize() const { return groupSize; }
void Cargo::setGroupSize(int size) { groupSize = size; }

std::vector<Cargo> Cargo::splitCargo(const std::vector<int>& splitSizes) const {
    std::vector<Cargo> splitParts;

    // Validate split sizes
    int totalSplitSize = 0;
    for (int size : splitSizes) {
        totalSplitSize += size;
    }

    if (totalSplitSize != groupSize) {
        throw invalid_argument("Split sizes must sum to original group size");
    }

    // Create split parts
    for (size_t i = 0; i < splitSizes.size(); ++i) {
        string splitID = getID() + "_SPLIT_" + to_string(i + 1);

        Cargo splitPart(splitID, getCity(), getTime(), splitSizes[i],
            getID(), groupSize, i + 1, splitSizes.size());

        splitParts.push_back(splitPart);
    }

    return splitParts;
}

bool Cargo::isSplitCargo() const { return isSplit; }
std::string Cargo::getOriginalCargoID() const { return originalCargoID; }
int Cargo::getOriginalGroupSize() const { return originalGroupSize; }
int Cargo::getSplitPartNumber() const { return splitPartNumber; }
int Cargo::getTotalSplitParts() const { return totalSplitParts; }
