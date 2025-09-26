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

    int minutes = local_tm.tm_hour * 60 + local_tm.tm_min;

    // If you want finer control, update config.h with start/end minutes.
    // For now, IRRIGATION_START_HOUR and IRRIGATION_END_HOUR are in hours only.
    int startMinutes = IRRIGATION_START_HOUR * 60;
    int endMinutes   = IRRIGATION_END_HOUR * 60;

    if (startMinutes <= endMinutes) {
        // Normal case (e.g. 07:00 - 08:00)
        return (minutes >= startMinutes) && (minutes < endMinutes);
    } else {
        // Wrap around midnight (e.g. 23:00 - 02:00)
        return (minutes >= startMinutes) || (minutes < endMinutes);
    }
}
