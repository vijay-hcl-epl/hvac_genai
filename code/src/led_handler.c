#include "led_handler.h"
#include "config_data_store.h"

void LEDHandler_Init(void) {
    // configure LED output GPIOs as needed
}

void LEDHandler_IndicatePosition(int pos) {
    for (int i = 0; i < ConfigDataStore_GetPositionCount(); i++) {
        ConfigDataStore_SetLED(i, (i == pos));
    }
}

void LEDHandler_IndicateError(void) {
    for (int i = 0; i < ConfigDataStore_GetPositionCount(); i++) {
        ConfigDataStore_SetLED(i, 0);
    }
}
