#ifndef SYSTEM_LOGIC_H
#define SYSTEM_LOGIC_H

#include <Arduino.h>

void systemInit();
void systemLoop();
bool isSystemIdle();
void startMovingToTray(int targetTray);

#endif

