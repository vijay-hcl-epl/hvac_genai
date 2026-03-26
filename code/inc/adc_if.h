#ifndef ADC_IF_H
#define ADC_IF_H
#include <stdint.h>
void AdcIf_Init(void);
uint16_t AdcIf_ReadRaw(void);
uint8_t AdcIf_GetPosition(void);
#endif
