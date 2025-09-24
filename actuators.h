
#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <chrono>

void pumpOn();
void pumpOff();
bool isPumpRunning();
std::chrono::steady_clock::duration pumpRunDuration();

#endif
