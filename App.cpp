#include "App.h"
#include <iostream>
using namespace std;

void App::run() {
    int choice;
    while (true) {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: loadData(); break;
        case 2: displayRecords(); break;
        case 3: modifyRecords(); break;
        case 4: generateSchedule(); break;
        case 5: showUnmatched(); break;
        case 6: saveSchedule(); break;
        case 7:
            cout << "Thank you. Have a nice day!\n";
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

void App::showMenu() {
    cout << "\n========== Freight & Cargo Scheduler ==========\n";
    cout << "1. Load Data from Files\n";
    cout << "2. Display All Records\n";
    cout << "3. Add/Edit/Delete Records\n";
    cout << "4. Generate Schedule\n";
    cout << "5. Show Unmatched Records\n";
    cout << "6. Save Schedule to File\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

void App::loadData() {
    string folderPath;
    cout << "Enter folder path (e.g., .): ";
    getline(cin, folderPath);

    if (folderPath.empty()) {
        cout << "Error: Folder path is empty!" << endl;
        return;
    }

    freightManager = FreightManager();
    cargoManager = CargoManager();

    freightManager.loadFromCSV(folderPath + "/freights.txt");
    cargoManager.loadFromCSV(folderPath + "/cargos.txt");

    int fCount = freightManager.getSize();
    int cCount = cargoManager.getSize();

    if (fCount > 0)
        cout << "Loaded " << fCount << " Freights.\n";
    else
        cout << "No freights found or failed to load freights.\n";

    if (cCount > 0)
        cout << "Loaded " << cCount << " Cargos.\n";
    else
        cout << "No cargos found or failed to load cargos.\n";
}

void App::displayRecords() {
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
}

void App::modifyRecords() {
    int subChoice;
    cout << "\n1. Add Freight  2. Edit Freight  3. Delete Freight\n";
    cout << "4. Add Cargo    5. Edit Cargo    6. Delete Cargo\n";
    cout << "Enter your choice: ";
    cin >> subChoice;
    cin.ignore();

    switch (subChoice) {
    case 1: { // Add Freight
        string id, city, type;
        int time;
        while (true) {
            cout << "Enter Freight ID: ";
            getline(cin, id);
            if (freightManager.existsByID(id)) {
                cout << "Freight ID already exists! Please enter a new ID.\n";
            }
            else {
                cout << "Enter City: ";
                getline(cin, city);
                cout << "Enter Time (e.g. 0930): ";
                cin >> time;
                cin.ignore();
                cout << "Enter Type (MiniMover/CargoCruiser/MegaCarrier): ";
                getline(cin, type);
                if (time < 0 || time > 2359 ||
                    (type != "MiniMover" && type != "CargoCruiser" && type != "MegaCarrier")) {
                    cout << "Invalid input. Try again.\n";
                }
                else {
                    freightManager.add(Freight(id, city, time, type));
                    cout << "Freight added successfully.\n";
                    break;
                }
            }
        }
        break;
    }

    case 2: { // Edit Freight
        string id;
        cout << "Enter Freight ID to edit: ";
        getline(cin, id);
        while (!freightManager.existsByID(id)) {
            cout << "Invalid ID! Enter again: ";
            getline(cin, id);
        }
        string newCity, newType;
        int newTime;
        cout << "Enter New City: ";
        getline(cin, newCity);
        cout << "Enter New Time: ";
        cin >> newTime;
        cin.ignore();
        cout << "Enter New Type: ";
        getline(cin, newType);
        if (newTime < 0 || newTime > 2359 ||
            (newType != "MiniMover" && newType != "CargoCruiser" && newType != "MegaCarrier")) {
            cout << "Invalid input.\n";
        }
        else {
            freightManager.edit(id, Freight(id, newCity, newTime, newType));
            cout << "Freight edited.\n";
        }
        break;
    }

    case 3: { // Delete Freight
        string id;
        cout << "Enter Freight ID to delete: ";
        getline(cin, id);
        while (!freightManager.existsByID(id)) {
            cout << "Invalid ID! Enter again: ";
            getline(cin, id);
        }
        char confirm;
        cout << "Confirm delete " << id << "? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            freightManager.remove(id);
            cout << "Deleted.\n";
        }
        else {
            cout << "Cancelled.\n";
        }
        break;
    }

    case 4: { // Add Cargo
        string id, city;
        int time, groupSize;
        while (true) {
            cout << "Enter Cargo ID: ";
            getline(cin, id);
            if (cargoManager.existsByID(id)) {
                cout << "ID exists! Enter again.\n";
            }
            else {
                cout << "Enter City: ";
                getline(cin, city);
                cout << "Enter Time: ";
                cin >> time;
                cout << "Enter Group Size (1-10): ";
                cin >> groupSize;
                cin.ignore();
                if (time < 0 || time > 2359 || groupSize < 1 || groupSize > 10) {
                    cout << "Invalid input.\n";
                }
                else {
                    cargoManager.add(Cargo(id, city, time, groupSize));
                    cout << "Cargo added.\n";
                    break;
                }
            }
        }
        break;
    }

    case 5: { // Edit Cargo
        string id;
        cout << "Enter Cargo ID to edit: ";
        getline(cin, id);
        while (!cargoManager.existsByID(id)) {
            cout << "Invalid ID! Enter again: ";
            getline(cin, id);
        }
        string newCity;
        int newTime, newGroupSize;
        cout << "Enter New City: ";
        getline(cin, newCity);
        cout << "Enter New Time: ";
        cin >> newTime;
        cout << "Enter New Group Size: ";
        cin >> newGroupSize;
        cin.ignore();
        if (newTime < 0 || newTime > 2359 || newGroupSize < 1 || newGroupSize > 10) {
            cout << "Invalid input.\n";
        }
        else {
            cargoManager.edit(id, Cargo(id, newCity, newTime, newGroupSize));
            cout << "Cargo edited.\n";
        }
        break;
    }

    case 6: { // Delete Cargo
        string id;
        cout << "Enter Cargo ID to delete: ";
        getline(cin, id);
        while (!cargoManager.existsByID(id)) {
            cout << "Invalid ID! Enter again: ";
            getline(cin, id);
        }
        char confirm;
        cout << "Confirm delete " << id << "? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            cargoManager.remove(id);
            cout << "Deleted.\n";
        }
        else {
            cout << "Cancelled.\n";
        }
        break;
    }

    default:
        cout << "Invalid choice.\n";
    }
}

void App::generateSchedule() {
    cout << "\nChoose scheduling strategy:\n";
    cout << "1. Prioritize on-time arrival\n";
    cout << "2. Minimize number of freights\n";
    cout << "Enter choice: ";

    int strategyChoice;
    cin >> strategyChoice;

    PriorityArrivalScheduler priorityScheduler;
    MinFreightScheduler minFreightScheduler;

    if (strategyChoice == 1) {
        scheduleManager.setScheduler(&priorityScheduler);
        cout << "Using: Priority Arrival Scheduler\n";
    }
    else if (strategyChoice == 2) {
        scheduleManager.setScheduler(&minFreightScheduler);
        cout << "Using: Minimize Freights Scheduler\n";
    }
    else {
        cout << "Invalid choice. Defaulting to Priority Arrival Scheduler.\n";
        scheduleManager.setScheduler(&priorityScheduler);
    }

    scheduleManager.generateSchedules(freightManager, cargoManager);

    int total = scheduleManager.getSize();
    if (total == 0) {
        cout << "No schedules generated.\n";
    }
    else {
        cout << "Generated " << total << " schedules:\n";
        scheduleManager.displaySchedules();
    }
}

void App::showUnmatched() {
    cout << "\n--- Unmatched Freights ---\n";
    scheduleManager.displayUnmatchedFreights();
    cout << "\n--- Unmatched Cargos ---\n";
    scheduleManager.displayUnmatchedCargos();
}

void App::saveSchedule() {
    string outputPath;
    cout << "Enter file path to save schedules: ";
    getline(cin >> ws, outputPath);
    scheduleManager.exportToCSV(outputPath);
    cout << "Schedules exported to " << outputPath << "\n";
}
