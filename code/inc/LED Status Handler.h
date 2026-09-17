#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdbool.h>
#include <stdint.h>

void LED_Status_Handler_Init(void);
void LED_Status_Handler_SetPowerLed(bool on);
void LED_Status_Handler_SetLedState(uint8_t position);
void LED_Status_Handler_IndicateError(void);
uint8_t LED_Status_Handler_GetLedBits(void);

#endif /* LED_STATUS_HANDLER_H */
