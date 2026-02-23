#ifndef STATUS_INDICATION_H
#define STATUS_INDICATION_H
#include <stdint.h>
void StatusIndication_Init(void);
void StatusIndication_SetPowerLED(uint8_t on_off);
void StatusIndication_SetPositionLED(uint8_t position);
#endif // STATUS_INDICATION_H
