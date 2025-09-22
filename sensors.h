#ifndef SENSORS_H
#define SENSORS_H

struct SensorData {
    int soilMoisture;   // percentage
    float temperature;  // °C
    float humidity;     // %
};

// Function to read simulated sensor data
SensorData readSensors();

#endif

