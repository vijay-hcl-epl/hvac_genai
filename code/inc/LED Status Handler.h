#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>

void LED_Status_Handler_Init(void);
void LED_Status_Handler_Set_Power_Led(uint8_t on);
void LED_Status_Handler_Set_Led_State(uint8_t position);
void LED_Status_Handler_Indicate_Error(void);
uint8_t LED_Status_Handler_Get_Position_State(void);

#endif
