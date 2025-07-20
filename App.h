#pragma once

#include "FileManager.h"
#include "FreightManager.h"
#include "CargoManager.h"
#include "ScheduleManager.h"
#include "PriorityArrivalScheduler.h"
#include "MinFreightScheduler.h"

class App {
    FreightManager freightManager;
    CargoManager cargoManager;
    ScheduleManager scheduleManager;
    FileManager fileManager;

public:
    void run();

private:
    void loadData();
    void displayRecords();
    void modifyRecords();
    void generateSchedule();
    void showUnmatched();
    void saveSchedule();

    void showMenu();
};

