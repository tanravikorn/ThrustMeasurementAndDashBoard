#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <Arduino.h>

extern volatile float g_current;
extern volatile float g_voltage;
extern volatile float g_power;
extern volatile float g_thrust;

extern SemaphoreHandle_t dataMutex;

#endif