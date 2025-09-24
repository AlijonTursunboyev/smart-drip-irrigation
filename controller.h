
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "sensors.h"

enum class Action {
    PUMP_OFF = 0,
    PUMP_ON  = 1
};

struct Decision {
    Action action;
    const char *reason; // short explanation
};

Decision decideAction(const SensorData &data, bool pumpCurrentlyRunning);

#endif
