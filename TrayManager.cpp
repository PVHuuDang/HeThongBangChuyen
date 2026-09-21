#include "TrayManager.h"
#include "Config.h"
#include <Preferences.h>

Preferences prefs;
bool khayCoHang[NUM_TRAYS + 1];
String khayID[NUM_TRAYS + 1];

void trayInit() {
    prefs.begin("trayData", false); 
    for (int i = 1; i <= NUM_TRAYS; i++) {
        String keyStatus = "status" + String(i);
        String keyID = "id" + String(i);
        khayCoHang[i] = prefs.getBool(keyStatus.c_str(), false);
        khayID[i] = prefs.getString(keyID.c_str(), "");
    }
}

int getEmptyTray() {
    for (int i = 1; i <= NUM_TRAYS; i++) {
        if (!khayCoHang[i]) return i;
    }
    return 0;
}

int getTrayById(String id) {
    for (int i = 1; i <= NUM_TRAYS; i++) {
        if (khayCoHang[i] && khayID[i] == id) return i;
    }
    return 0;
}

void assignTray(int trayIndex, String id) {
    if (trayIndex > 0 && trayIndex <= NUM_TRAYS) {
        khayCoHang[trayIndex] = true;
        khayID[trayIndex] = id;
        
        prefs.putBool(("status" + String(trayIndex)).c_str(), true);
        prefs.putString(("id" + String(trayIndex)).c_str(), id);
    }
}

void clearTray(int trayIndex) {
    if (trayIndex > 0 && trayIndex <= NUM_TRAYS) {
        khayCoHang[trayIndex] = false;
        khayID[trayIndex] = "";
        
        prefs.putBool(("status" + String(trayIndex)).c_str(), false);
        prefs.putString(("id" + String(trayIndex)).c_str(), "");
    }
}

