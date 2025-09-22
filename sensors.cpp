#include "sensors.h"
#include <cstdlib>
#include <ctime>

SensorData readSensors() {
    SensorData data;
    data.soilMoisture = rand() % 101;        // 0 - 100 %
    data.temperature  = 15 + rand() % 20;    // 15 - 35 °C
    data.humidity     = 30 + rand() % 50;    // 30 - 80 %
    return data;
}

