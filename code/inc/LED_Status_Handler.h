#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

void LED_Status_Handler_Init(void);
void LED_Status_Handler_Set_Position(uint8_t position);
void LED_Status_Handler_Indicate_Error(void);
void LED_Status_Handler_Set_PowerLed(void);

#endif // LED_STATUS_HANDLER_H
