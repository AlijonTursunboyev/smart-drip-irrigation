#include "logger.h"
#include "config.h"
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <iostream>

static std::ofstream g_csv;

void writeCsvHeader(std::ofstream &f) {
    f << "timestamp,soilMoisture,temperature,humidity,pumpStatus,reason\n";
}

void initLogger() {
    bool exists = false;
    // simplistic check: try to open for read
    std::ifstream in(config::LOG_CSV_FILE); // but we don't have namespace config - I'll just open directly below
    if (in.good()) exists = true;
    in.close();

    g_csv.open(LOG_CSV_FILE, std::ios::app);
    if (!exists) writeCsvHeader(g_csv);
}

static std::string currentIsoTimestamp() {
    using namespace std::chrono;
    auto now = system_clock::now();
    time_t t = system_clock::to_time_t(now);
    struct tm tmstruct;
#if defined(_WIN32)
    gmtime_s(&tmstruct, &t);
#else
    gmtime_r(&t, &tmstruct);
#endif
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &tmstruct);
    return std::string(buf);
}

void logRecord(const SensorData &d, bool pumpState, const std::string &reason) {
    if (!g_csv.is_open()) {
        g_csv.open(LOG_CSV_FILE, std::ios::app);
    }
    std::string ts = currentIsoTimestamp();
    g_csv << ts << "," 
          << d.soilMoisture << ","
          << d.temperature << ","
          << d.humidity << ","
          << (pumpState ? 1 : 0) << ","
          << "\"" << reason << "\"\n";
    g_csv.flush();
    // also simple console log
    std::cout << "[LOG] " << ts << " soil=" << d.soilMoisture << "% pump=" << (pumpState ? "ON":"OFF") 
              << " reason=" << reason << std::endl;
}
