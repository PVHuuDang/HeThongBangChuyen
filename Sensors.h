#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

void sensorsInit();
bool isGocPressed();
bool isServoPressed();
bool isCuaPressed();
bool checkDemKhayPulse(); 

#endif

