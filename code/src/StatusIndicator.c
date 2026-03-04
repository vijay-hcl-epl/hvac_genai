#include "StatusIndicator.h"
#include <stdint.h>

void StatusIndicator_Init(void) {
    // Initialize all status LEDs to OFF
}

void StatusIndicator_SetStatus(StatusType type) {
    // Control status LED: IDLE, MOVING, REACHED, ERROR
    (void)type;
}

void StatusIndicator_SetPosition(uint8_t pos) {
    // Activate one of 6 LEDs based on flap position
    (void)pos;
}
