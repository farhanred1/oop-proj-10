#include "FileManager.h"
#include "FreightManager.h"
#include "CargoManager.h"
#include "ScheduleManager.h"

int main() {
    FreightManager freightManager;
    CargoManager cargoManager;
    ScheduleManager scheduleManager;
    FileManager fileManager;

    string folderPath;
    int choice;

    while (true) {
        cout << "\n========== Freight & Cargo Scheduler ==========\n";
        cout << "1. Load Data from Files\n";
        cout << "2. Display All Records\n";
        cout << "3. Add/Edit/Delete Records\n";
        cout << "4. Generate Schedule\n";
        cout << "5. Show Unmatched Records\n";
        cout << "6. Save Schedule to File\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To clear the input buffer

        switch (choice) {
        case 1: {
            std::cout << "Enter folder path (e.g., .): ";
            std::getline(std::cin, folderPath);

            if (folderPath.empty()) {
                std::cout << "Error: Folder path is empty!" << std::endl;
                break;
            }

            // Reset managers
            freightManager = FreightManager();
            cargoManager = CargoManager();

            // Load data via manager methods
            freightManager.loadFromCSV(folderPath + "/freights.txt");
            cargoManager.loadFromCSV(folderPath + "/cargos.txt");

            // Display how many were loaded
            int fCount = freightManager.getSize();
            int cCount = cargoManager.getSize();

            if (fCount > 0)
                std::cout << "Loaded " << fCount << " Freights.\n";
            else
                std::cout << "No freights found or failed to load freights.\n";

            if (cCount > 0)
                std::cout << "Loaded " << cCount << " Cargos.\n";
            else
                std::cout << "No cargos found or failed to load cargos.\n";

            break;
        }

        case 2: {
            cout << "\n--- All Freights ---\n";
            if (freightManager.getSize() == 0) {
                cout << "No freights available.\n";
            }
            else {
                for (int i = 0; i < freightManager.getSize(); ++i) {
                    Freight freight = freightManager.getByIndex(i);
                    freight.displayInfo();
                }
            }

            cout << "\n--- All Cargos ---\n";
            if (cargoManager.getSize() == 0) {
                cout << "No cargos available.\n";
            }
            else {
                for (int i = 0; i < cargoManager.getSize(); ++i) {
                    Cargo cargo = cargoManager.getByIndex(i);
                    cargo.displayInfo();
                }
            }
            break;
        }
        case 3: {
            int subChoice;
            cout << "\n1. Add Freight  2. Edit Freight  3. Delete Freight\n";
            cout << "4. Add Cargo    5. Edit Cargo    6. Delete Cargo\n";
            cout << "Enter your choice: ";
            cin >> subChoice;
            cin.ignore(); // clear the buffer

            switch (subChoice) {
            case 1: {
                string id, city;
                int time;

                while (true) {
                    cout << "Enter Freight ID: ";
                    getline(cin, id);

                    // Check if Freight ID already exists
                    if (freightManager.existsByID(id)) {
                        cout << "Freight ID already exists! Please enter a new ID." << endl;
                    }
                    else {
                        cout << "Enter City: "; getline(cin, city);
                        cout << "Enter Time (e.g. 0930): "; cin >> time;

                        // Validate time format (basic check for a 4-digit number)
                        if (time < 0 || time > 2359) {
                            cout << "Invalid time format!" << endl;
                        }
                        else {
                            freightManager.add(Freight(id, city, time));
                            cout << "Freight added successfully.\n";
                            break;  // Exit the loop after successfully adding the freight
                        }
                    }
                }
                break;
            }

            case 2: { // Edit Freight
                string id;
                cout << "Enter Freight ID to edit: "; getline(cin, id);

                // Loop until a valid Freight ID is entered
                while (!freightManager.existsByID(id)) {
                    cout << "Invalid Freight ID! Please enter a valid Freight ID: ";
                    getline(cin, id);
                }

                // Proceed with editing
                string newCity;
                int newTime;
                cout << "Enter New City: "; getline(cin, newCity);
                cout << "Enter New Time: "; cin >> newTime;

                // Validate time format (basic check for a 4-digit number)
                if (newTime < 0 || newTime > 2359) {
                    cout << "Invalid time format!" << endl;
                }
                else {
                    freightManager.edit(id, Freight(id, newCity, newTime));
                    cout << "Freight edited successfully.\n";
                }
                break;
            }


            case 3: { // Delete Freight
                string id;
                cout << "Enter Freight ID to delete: "; getline(cin, id);

                // Loop until a valid Freight ID is entered
                while (!freightManager.existsByID(id)) {
                    cout << "Invalid Freight ID! Please enter a valid Freight ID: ";
                    getline(cin, id);
                }

                // Confirm deletion
                char confirm;
                cout << "Are you sure you want to delete Freight ID " << id << "? (y/n): ";
                cin >> confirm;

                if (confirm == 'y' || confirm == 'Y') {
                    freightManager.remove(id);
                    cout << "Freight " << id << " deleted successfully!" << endl;
                }
                else {
                    cout << "Deletion cancelled." << endl;
                }
                break;
            }


            case 4: {
                string id, city;
                int time;

                while (true) {
                    cout << "Enter Cargo ID: ";
                    getline(cin, id);

                    // Check if Cargo ID already exists
                    if (cargoManager.existsByID(id)) {
                        cout << "Cargo ID already exists! Please enter a new ID." << endl;
                    }
                    else {
                        cout << "Enter City: "; getline(cin, city);
                        cout << "Enter Time (e.g. 0930): "; cin >> time;

                        // Validate time format (basic check for a 4-digit number)
                        if (time < 0 || time > 2359) {
                            cout << "Invalid time format!" << endl;
                        }
                        else {
                            cargoManager.add(Cargo(id, city, time));
                            cout << "Cargo added successfully.\n";
                            break;  // Exit the loop after successfully adding the cargo
                        }
                    }
                }
                break;
            }

            case 5: { // Edit Cargo
                string id;
                cout << "Enter Cargo ID to edit: "; getline(cin, id);

                // Loop until a valid Cargo ID is entered
                while (!cargoManager.existsByID(id)) {
                    cout << "Invalid Cargo ID! Please enter a valid Cargo ID: ";
                    getline(cin, id);
                }

                // Proceed with editing
                string newCity;
                int newTime;
                cout << "Enter New City: "; getline(cin, newCity);
                cout << "Enter New Time: "; cin >> newTime;

                // Validate time format (basic check for a 4-digit number)
                if (newTime < 0 || newTime > 2359) {
                    cout << "Invalid time format!" << endl;
                }
                else {
                    cargoManager.edit(id, Cargo(id, newCity, newTime));
                    cout << "Cargo edited successfully.\n";
                }
                break;
            }


            case 6: { // Delete Cargo
                string id;
                cout << "Enter Cargo ID to delete: "; getline(cin, id);

                // Loop until a valid Cargo ID is entered
                while (!cargoManager.existsByID(id)) {
                    cout << "Invalid Cargo ID! Please enter a valid Cargo ID: ";
                    getline(cin, id);
                }

                // Confirm deletion
                char confirm;
                cout << "Are you sure you want to delete Cargo ID " << id << "? (y/n): ";
                cin >> confirm;

                if (confirm == 'y' || confirm == 'Y') {
                    cargoManager.remove(id);
                    cout << "Cargo " << id << " deleted successfully!" << endl;
                }
                else {
                    cout << "Deletion cancelled." << endl;
                }
                break;
            }

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }

            break;
        }

        case 4: {
            scheduleManager.generateSchedules(freightManager, cargoManager);
            int total = scheduleManager.getSize();
            if (total == 0) {
                cout << "No schedules generated.\n";
            }
            else {
                for (int i = 0; i < total; ++i) {
                    cout << "Schedule " << i + 1 << endl;
                    scheduleManager.getByIndex(i).displaySchedule();
                    cout << endl;
                }
            }
            break;
        }

        case 5: {
            cout << "\n--- Unmatched Freights ---\n";
            scheduleManager.displayUnmatchedFreights();
            cout << "\n--- Unmatched Cargos ---\n";
            scheduleManager.displayUnmatchedCargos();
            break;
        }

        case 6: {
            std::string outputPath;
            std::cout << "Enter file path to save schedules (e.g., schedules.csv): ";
            std::getline(std::cin >> std::ws, outputPath);
            scheduleManager.exportToCSV(outputPath);
            std::cout << "Schedules exported successfully to " << outputPath << "\n";
            break;
        }

        case 7:
            cout << "Thank you. Have a nice day!\n";
            return 0;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
