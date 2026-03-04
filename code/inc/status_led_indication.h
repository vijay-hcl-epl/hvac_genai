#ifndef STATUS_LED_INDICATION_H
#define STATUS_LED_INDICATION_H
#include <stdint.h>
#include <stdbool.h>

void StatusLED_Set(uint8_t pos);
void StatusLED_ShowPower(bool on);

#endif // STATUS_LED_INDICATION_H
