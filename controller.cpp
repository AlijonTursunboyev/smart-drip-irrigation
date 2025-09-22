
#include "controller.h"

const int MOISTURE_THRESHOLD = 40;

bool decideAction(const SensorData &data) {
    return data.soilMoisture < MOISTURE_THRESHOLD; // true = pump ON
}
