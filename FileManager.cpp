// Author: Alastair Gillyson Lamiao Madrid

#include "FileManager.h"
#include <fstream>
#include <sstream>


std::vector<std::vector<std::string>> FileManager::loadCSV(const std::string& filepath) {
    std::vector<std::vector<std::string>> rows;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        // Do not print. Let caller handle failure.
        return rows;
    }

    std::string line;
    while (getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        rows.push_back(row);
    }

    file.close();
    return rows;
}

void FileManager::saveCSV(const std::string& filepath, const std::vector<std::vector<std::string>>& data) {
    std::ofstream file(filepath);

    if (!file.is_open()) return;

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1)
                file << ",";
        }
        file << "\n";
    }

    file.close();
}

// Author: Alastair Gillyson Lamiao Madrid