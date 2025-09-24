#ifndef LOGGER_H
#define LOGGER_H

#include "sensors.h"
#include <string>

void initLogger();
void logRecord(const SensorData &d, bool pumpState, const std::string &reason);

#endif
