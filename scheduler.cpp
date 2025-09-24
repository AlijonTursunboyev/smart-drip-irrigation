#include "scheduler.h"
#include "config.h"
#include <chrono>
#include <ctime>

bool isWithinIrrigationWindow() {
    using namespace std::chrono;
    auto now = system_clock::now();
    time_t t = system_clock::to_time_t(now);
    struct tm local_tm;
#if defined(_WIN32)
    localtime_s(&local_tm, &t);
#else
    localtime_r(&t, &local_tm);
#endif

    int hour = local_tm.tm_hour;
    // If start <= end (normal, e.g., 7-8)
    if (IRRIGATION_START_HOUR <= IRRIGATION_END_HOUR) {
        return (hour >= IRRIGATION_START_HOUR) && (hour < IRRIGATION_END_HOUR);
    } else {
        // wrap-around midnight (e.g., 23 - 2)
        return (hour >= IRRIGATION_START_HOUR) || (hour < IRRIGATION_END_HOUR);
    }
}
