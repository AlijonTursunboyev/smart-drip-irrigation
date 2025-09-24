#ifndef CONFIG_H
#define CONFIG_H

// Thresholds
static const int SOIL_MOISTURE_THRESHOLD = 40; // percent
static const int SOIL_MOISTURE_HYSTERESIS = 5; // percent - prevents chattering

// Scheduler - irrigation daily window (24-hour)
static const int IRRIGATION_START_HOUR = 7;  // 07:00
static const int IRRIGATION_END_HOUR   = 8;  // 08:00

// Safety
static const int PUMP_MAX_RUNTIME_SECONDS = 60 * 5; // 5 minutes max continuous run

// Logging
static const char *LOG_CSV_FILE = "data.csv";

#endif // CONFIG_H
