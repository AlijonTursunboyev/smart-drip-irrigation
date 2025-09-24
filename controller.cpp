
#include "controller.h"
#include "config.h"
#include <string>

Decision decideAction(const SensorData &data, bool pumpCurrentlyRunning) {
    // Use hysteresis:
    // - turn ON when soil < threshold - hysteresis/2
    // - turn OFF when soil > threshold + hysteresis/2
    int onLimit  = SOIL_MOISTURE_THRESHOLD - (SOIL_MOISTURE_HYSTERESIS / 2);
    int offLimit = SOIL_MOISTURE_THRESHOLD + (SOIL_MOISTURE_HYSTERESIS / 2);

    if (pumpCurrentlyRunning) {
        if (data.soilMoisture >= offLimit) {
            return {Action::PUMP_OFF, "moisture above off limit (hysteresis)"}; 
        } else {
            return {Action::PUMP_ON, "still below off limit, keep running"};
        }
    } else {
        if (data.soilMoisture <= onLimit) {
            return {Action::PUMP_ON, "moisture below on limit (need water)"};
        } else {
            return {Action::PUMP_OFF, "moisture OK"};
        }
    }
}
