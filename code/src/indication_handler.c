#include "indication_handler.h"
// LED bitmaps: 6 pos LEDs, 1 status LED
static uint8_t led_state = 0x00;
static uint8_t status_code_var = 0x00;

int IndicationHandler_Update(int position, int status_code) {
    // Only one position LED active at a time
    if (position < 0 || position > 5)
        return -1;
    led_state = (1 << position);
    status_code_var = (uint8_t)status_code;
    // TODO: Hardware-specific: set GPIO levels for LEDs here
    return 0;
}

void IndicationHandler_AllOff(void) {
    led_state = 0x00;
    status_code_var = 0x00;
    // TODO: Hardware-specific: turn all LEDs off
}
