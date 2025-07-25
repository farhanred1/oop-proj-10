// FileManager.h
// Author: Alastair Gillyson Lamiao Madrid
#pragma once
#include "Freight.h"
#include "Cargo.h"
#include "ScheduleManager.h"

#include <string>
#include <vector>

class FileManager {
public:
    /**
     * Loads a CSV file and returns its contents as a vector of string vectors.
     * Each inner vector represents a row of cells.
     * No type conversion is done; all values are strings.
     *
     * @param filepath Path to the CSV file.
     * @return Vector of rows, each row is a vector of strings.
     */
    static std::vector<std::vector<std::string>> loadCSV(const std::string& filepath);

    /**
     * Saves data to a CSV file. Each row is a vector of strings.
     *
     * @param filepath Path where the CSV will be saved.
     * @param data A vector of rows, where each row is a vector of strings.
     */
    static void saveCSV(const std::string& filepath, const std::vector<std::vector<std::string>>& data);
};
