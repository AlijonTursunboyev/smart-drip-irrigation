#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include "sensors.h"
#include "actuators.h"
#include "controller.h"

using namespace std;

int main() {
    srand(time(0));

    ofstream logFile("data.csv");
    logFile << "soilMoisture,temperature,humidity,pumpStatus\n";

    for (int i = 0; i < 10; i++) {
        SensorData data = readSensors();

        bool pumpStatus = decideAction(data);

        // Print sensor data
        cout << "Soil Moisture: " << data.soilMoisture << "% | "
             << "Temp: " << data.temperature << "°C | "
             << "Humidity: " << data.humidity << "% | ";

        if (pumpStatus) pumpOn();
        else pumpOff();

        // Log data
        logFile << data.soilMoisture << ","
                << data.temperature << ","
                << data.humidity << ","
                << (pumpStatus ? 1 : 0) << "\n";

        this_thread::sleep_for(chrono::seconds(1));
    }

    logFile.close();
    cout << "Data logged to data.csv ✅" << endl;
    return 0;
}

