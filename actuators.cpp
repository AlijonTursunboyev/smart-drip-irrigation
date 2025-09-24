#include "actuators.h"
#include <iostream>
#include <chrono>
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

chrono::steady_clock::duration pumpRunDuration() {
    if (!pump_state)
        return chrono::steady_clock::duration::zero();
    return chrono::steady_clock::now() - pump_start_time;
}
