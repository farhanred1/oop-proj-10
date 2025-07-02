// FileManager.cpp
#include "FileManager.h"
#include <fstream>
#include <sstream>

vector<Freight> FileManager::loadFreights(const string& path) {
    vector<Freight> freights;
    ifstream file(path);

    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return freights;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, city;
        int time;

        getline(ss, id, ',');  // Extract the Freight ID
        getline(ss, city, ',');  // Extract the City (refuel stop)
        ss >> time;  // Extract the refuel time

        // Create Freight object and add to the list
        freights.push_back(Freight(id, city, time));
    }

    file.close();
    cout << "Freight data loaded successfully.\n";
    return freights;
}

vector<Cargo> FileManager::loadCargos(const string& path) {
    vector<Cargo> cargos;
    ifstream file(path);

    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return cargos;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, city;
        int time;

        getline(ss, id, ',');  // Extract the Cargo ID
        getline(ss, city, ',');  // Extract the Destination City
        ss >> time;  // Extract the required time to reach destination

        // Create Cargo object and add to the list
        cargos.push_back(Cargo(id, city, time));
    }

    file.close();
    cout << "Cargo data loaded successfully.\n";
    return cargos;
}

void FileManager::saveSchedules(const ScheduleManager& manager, const string& filepath) {
    ofstream outFile(filepath);

    if (!outFile.is_open()) {
        cerr << "Error: Could not open file " << filepath << " for writing.\n";
        return;
    }

    outFile << "Freight ID,City,Time,Cargo ID,City,Time\n";
    int total = manager.getSize();
    for (int i = 0; i < total; ++i) {
        Schedule schedule = manager.getByIndex(i);
        outFile << schedule.getFreight().getID() << ","
            << schedule.getFreight().getCity() << ","
            << schedule.getFreight().getTime() << ","
            << schedule.getCargo().getID() << ","
            << schedule.getCargo().getCity() << ","
            << schedule.getCargo().getTime() << "\n";
    }

    outFile.close();
    cout << "Schedules saved to " << filepath << " successfully.\n";
}