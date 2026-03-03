#ifndef FEEDBACK_HANDLING_H
#define FEEDBACK_HANDLING_H

#include <stdint.h>
#include <stdbool.h>

#define FEEDBACK_ADC_MIN 100
#define FEEDBACK_ADC_MAX 900
#define FEEDBACK_DISCRETE_MIN 0
#define FEEDBACK_DISCRETE_MAX 5

void FEEDBACK_Init(void);
int FEEDBACK_ReadPosition(void);
bool FEEDBACK_IsValid(void);
void FEEDBACK_UpdateADCValue(uint16_t adc_value);

#endif // FEEDBACK_HANDLING_H
