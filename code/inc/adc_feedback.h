#ifndef ADC_FEEDBACK_H
#define ADC_FEEDBACK_H
#include <stdbool.h>
#include <stdint.h>
void ADCFbk_Init(void);
void ADCFbk_GetPosition(uint8_t *value, bool *error);
#endif // ADC_FEEDBACK_H
