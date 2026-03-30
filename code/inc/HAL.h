#ifndef HAL_H
#define HAL_H
#include <stdint.h>
void HAL_Init(void);
uint16_t HAL_GetADC(void);
void HAL_SetGreenLED(uint8_t pos);
void HAL_StopMotor(void);
void HAL_MoveMotor(uint8_t direction);
void HAL_UARTSend(uint8_t data);
uint8_t HAL_UARTReceive(void);
#endif // HAL_H
