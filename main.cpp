// main.cpp - Enhanced Version with Cargo Splitting Support and Original UI
#include "FileManager.h"
#include "FreightManager.h"
#include "CargoManager.h"
#include "ScheduleManager.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    FreightManager freightManager;
    CargoManager cargoManager;
    ScheduleManager scheduleManager;
    FileManager fileManager;

    string folderPath;
    int choice;

    while (true) {
        cout << "\n========== Enhanced Freight & Cargo Scheduler ==========\n";
        cout << "1. Load Data from Files\n";
        cout << "2. Display All Records\n";
        cout << "3. Add/Edit/Delete Records\n";
        cout << "4. Generate Schedule (Time Priority)\n";
        cout << "5. Generate Schedule (Capacity Optimization)\n";
        cout << "6. Show Unmatched Records\n";
        cout << "7. Save Schedule to File\n";
        cout << "8. Display Detailed Statistics\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // clear input buffer

        switch (choice) {
        case 1: {
            cout << "Enter folder path (e.g., .): ";
            getline(cin, folderPath);
            if (folderPath.empty()) {
                cout << "Error: Folder path is empty!\n";
                break;
            }
            freightManager = FreightManager();
            cargoManager = CargoManager();
            freightManager.loadFromCSV(folderPath + "/freights.txt");
            cargoManager.loadFromCSV(folderPath + "/cargos.txt");
            cout << "Loaded " << freightManager.getSize() << " Freights.\n";
            cout << "Loaded " << cargoManager.getSize() << " Cargos.\n";
            break;
        }
        case 2: {
            cout << "\n--- All Freights ---\n";
            if (freightManager.getSize() == 0) {
                cout << "No freights available.\n";
            }
            else {
                for (int i = 0; i < freightManager.getSize(); ++i) {
                    freightManager.getByIndex(i).displayInfo();
                }
            }
            cout << "\n--- All Cargos ---\n";
            if (cargoManager.getSize() == 0) {
                cout << "No cargos available.\n";
            }
            else {
                for (int i = 0; i < cargoManager.getSize(); ++i) {
                    cargoManager.getByIndex(i).displayInfo();
                }
            }
            break;
        }
        case 3: {
            int sub;
            cout << "\n1. Add Freight   2. Edit Freight   3. Delete Freight\n";
            cout << "4. Add Cargo     5. Edit Cargo     6. Delete Cargo\n";
            cout << "Enter your choice: ";
            cin >> sub;
            cin.ignore();

            if (sub == 1) {
                string id, city, type; int time;
                cout << "Enter Freight ID: "; getline(cin, id);
                cout << "Enter City: "; getline(cin, city);
                cout << "Enter Time (e.g. 0930): "; cin >> time; cin.ignore();
                cout << "Enter Type (MiniMover/CargoCruiser/MegaCarrier): "; getline(cin, type);
                freightManager.add(Freight(id, city, time, type));
                cout << "Freight added successfully.\n";
            }
            else if (sub == 2) {
                string id; cout << "Enter Freight ID to edit: "; getline(cin, id);
                string city, type; int time;
                cout << "Enter New City: "; getline(cin, city);
                cout << "Enter New Time: "; cin >> time; cin.ignore();
                cout << "Enter New Type: "; getline(cin, type);
                freightManager.edit(id, Freight(id, city, time, type));
                cout << "Freight edited successfully.\n";
            }
            else if (sub == 3) {
                string id; cout << "Enter Freight ID to delete: "; getline(cin, id);
                freightManager.remove(id);
                cout << "Freight deleted successfully.\n";
            }
            else if (sub == 4) {
                string id, city; int time, size;
                cout << "Enter Cargo ID: "; getline(cin, id);
                cout << "Enter City: "; getline(cin, city);
                cout << "Enter Time: "; cin >> time;
                cout << "Enter Group Size (1–10): "; cin >> size; cin.ignore();
                cargoManager.add(Cargo(id, city, time, size));
                cout << "Cargo added successfully.\n";
            }
            else if (sub == 5) {
                string id; cout << "Enter Cargo ID to edit: "; getline(cin, id);
                string city; int time, size;
                cout << "Enter New City: "; getline(cin, city);
                cout << "Enter New Time: "; cin >> time;
                cout << "Enter New Group Size: "; cin >> size; cin.ignore();
                cargoManager.edit(id, Cargo(id, city, time, size));
                cout << "Cargo edited successfully.\n";
            }
            else if (sub == 6) {
                string id; cout << "Enter Cargo ID to delete: "; getline(cin, id);
                cargoManager.remove(id);
                cout << "Cargo deleted successfully.\n";
            }
            else {
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 4: {
            cout << "\n=== Generating Time Priority Schedule ===\n";
            scheduleManager.generateSchedules(freightManager, cargoManager, SchedulingMode::TIME_PRIORITY);
            for (int i = 0; i < scheduleManager.getSize(); ++i) {
                cout << "\nSchedule " << (i + 1) << ":\n";
                scheduleManager.getByIndex(i).displayScheduleWithTiming();
            }
            break;
        }
        case 5: {
            cout << "\n=== Generating Capacity Optimization Schedule ===\n";
            scheduleManager.generateSchedules(freightManager, cargoManager, SchedulingMode::CAPACITY_OPTIMIZATION);
            for (int i = 0; i < scheduleManager.getSize(); ++i) {
                cout << "\nSchedule " << (i + 1) << ":\n";
                scheduleManager.getByIndex(i).displayDetailedSchedule();
            }
            break;
        }
        case 6: {
            cout << "\n--- Unmatched Freights ---\n";
            scheduleManager.displayUnmatchedFreights();
            cout << "\n--- Unmatched Cargos ---\n";
            scheduleManager.displayUnmatchedCargos();
            break;
        }
        case 7: {
            string path;
            cout << "Enter file path to save schedules: "; getline(cin, path);
            scheduleManager.exportToCSV(path);
            cout << "Schedules saved to " << path << "\n";
            break;
        }
        case 8: {
            cout << "\n=== Detailed Statistics ===\n";
            scheduleManager.displayDetailedStatistics();
            break;
        }
        case 9:
            cout << "Exiting. Have a great day!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
