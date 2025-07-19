// RecordManager.h
#pragma once
#include <vector>
#include <string>

template<typename T>
class RecordManager {
protected:
    std::vector<T> records;

public:
    virtual ~RecordManager() = default;

    virtual void add(const T& record) {
        records.push_back(record);
    }

    virtual void edit(const std::string& id, const T& updatedRecord) {
        for (auto& r : records) {
            if (r.getID() == id) {
                r = updatedRecord;
                return;
            }
        }
    }

    virtual void remove(const std::string& id) {
        records.erase(
            std::remove_if(records.begin(), records.end(),
                [&id](const T& r) { return r.getID() == id; }),
            records.end()
        );
    }

    virtual T getByIndex(int index) const {
        return records.at(index);
    }

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

    auto begin() { return records.begin(); }
    auto end() { return records.end(); }

    auto begin() const { return records.begin(); }
    auto end() const { return records.end(); }

};