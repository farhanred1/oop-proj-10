// RecordManager.h
#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

template<typename T>
class RecordManager {
protected:
    vector<T> records;
    vector<T> unmatchedRecords;

public:
    virtual ~RecordManager() = default;

    virtual void add(const T& record) {
        records.push_back(record);
    }

    virtual void edit(const string& id, const T& record) {
        for (auto& r : records) {
            if (r.getID() == id) {
                r = record;
                return;
            }
        }
    }

    virtual void remove(const string& id) {
        records.erase(
            remove_if(records.begin(), records.end(),
                [&id](const T& r) { return r.getID() == id; }),
            records.end()
        );
    }

    virtual T getByIndex(int index) const {
        return records.at(index);
    }

    // Check if a record exists by ID
    virtual bool existsByID(const std::string& id) const {
        for (const auto& r : records) {
            if (r.getID() == id) {
                return true;
            }
        }
        return false;
    }

    virtual int getSize() const {
        return static_cast<int>(records.size());
    }

    virtual void addUnmatched(const T& record) {
        unmatchedRecords.push_back(record);
    }

    virtual void printUnmatched() const {
        for (const auto& r : unmatchedRecords) {
            r.displayInfo();
        }
    }
};