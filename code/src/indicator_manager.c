#include "indicator_manager.h"
#include <stdint.h>
// Hardware abstraction mocks
static void GPIO_SetPowerLED(bool on) { (void)on; }
static void GPIO_SetPosLED(uint8_t idx, bool on) { (void)idx; (void)on; }

void IndicatorManager_Init(void) {
    GPIO_SetPowerLED(true);
    for(uint8_t i=0; i<6; ++i) GPIO_SetPosLED(i, false);
}

void IndicatorManager_Update(uint8_t position) {
    GPIO_SetPowerLED(true);
    for(uint8_t i=0; i<6; ++i) GPIO_SetPosLED(i, false);
    if (position < 6) {
        GPIO_SetPosLED(position, true);
    }
    // if 0xFF (error), all position LEDs off
}
