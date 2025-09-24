#include "actuators.h"
#include <iostream>
#include <chrono>
#include<config.h>
using namespace std;

static bool pump_state = false;
static chrono::steady_clock::time_point pump_start_time;

void pumpOn() {
    if (!pump_state) {
        pump_state = true;
        pump_start_time = chrono::steady_clock::now();
        cout << "[ACTUATOR] Pump ON 💧" << endl;
    } else {
        // already on
    }
}

void pumpOff() {
    if (pump_state) {
        pump_state = false;
        auto run = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - pump_start_time).count();
        cout << "[ACTUATOR] Pump OFF ❌ (ran " << run << "s)" << endl;
    }
}

bool isPumpRunning() {
    return pump_state;
}

void checkPumpSafety() {
    if (pump_state) {
        auto run_seconds = chrono::duration_cast<chrono::seconds>(
            chrono::steady_clock::now() - pump_start_time
        ).count();

        if (run_seconds > PUMP_MAX_RUNTIME_SECONDS) {
            pumpOff();
            cout << "[SAFETY] Pump stopped after exceeding max runtime!" << endl;
        }
    }
}

chrono::steady_clock::duration pumpRunDuration() {
    if (!pump_state)
        return chrono::steady_clock::duration::zero();
    return chrono::steady_clock::now() - pump_start_time;
}
