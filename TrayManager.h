#ifndef TRAY_MANAGER_H
#define TRAY_MANAGER_H

#include <Arduino.h>

void trayInit();
int getEmptyTray();
int getTrayById(String id);
void assignTray(int trayIndex, String id);
void clearTray(int trayIndex);

#endif

