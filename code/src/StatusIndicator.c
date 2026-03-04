#include "StatusIndicator.h"
#include "GPIO.h"
void StatusIndicator_Init(void) {}
void StatusIndicator_SetStatus(uint8_t status) {
    if (status)
        GPIO_Set(2); // Power/status LED
    else
        GPIO_Clear(2);
}
void StatusIndicator_SetPositionLed(uint8_t position) {
    for(uint8_t i=3; i<=8; ++i)
        GPIO_Clear(i); // Assume 6 positions mapped to GPIO 3-8
    if(position < 6)
        GPIO_Set(position+3);
}
