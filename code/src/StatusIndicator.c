/* StatusIndicator.c - LED control logic for system and position indication. */
#include "StatusIndicator.h"
#include "GPIO.h"

void StatusIndicator_Init(void) {
    GPIO_SetStatusLED(true);
    StatusIndicator_Update(0);
}

void StatusIndicator_Update(uint8_t position) {
    GPIO_SetAllGreenLEDs(false);
    if (position <= 5)
        GPIO_SetGreenLED(position, true);
}

void StatusIndicator_ShowError(void) {
    GPIO_SetStatusLED(false);
}
