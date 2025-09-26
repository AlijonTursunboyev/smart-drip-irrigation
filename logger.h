#ifndef LOGGER_H
#define LOGGER_H

#include "sensors.h"
#include "config.h"   // include config separately
#include <string>

void initLogger();
void logRecord(const SensorData &d, bool pumpState, const std::string &reason);

#endif
