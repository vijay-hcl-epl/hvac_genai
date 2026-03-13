#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <stdint.h>

#define ERR_NONE         0x00
#define ERR_CMD_INVALID  0x01
#define ERR_ADC_OOR      0x02
#define ERR_MOTOR_FAULT  0x04
#define ERR_HW_FAULT     0x08

void ErrorHandler_Init(void);
void ErrorHandler_Set(uint8_t code);
void ErrorHandler_Clear(void);
uint8_t ErrorHandler_GetFlags(void);

#endif // ERROR_HANDLER_H
