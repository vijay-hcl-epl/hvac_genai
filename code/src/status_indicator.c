#include "status_indicator.h"
#include <stm32f4xx.h>
static uint8_t LastKnownPos = 0;
void StatusLED_set(uint8_t pos) {
    LastKnownPos = pos;
    // TODO: Set position LED pins: Only ONE green LED ON at any time
}
void PowerLED_on(void) {
    // TODO: Set status LED ON
}
void status_indicator_init(void) {
    LastKnownPos = 0;
}
