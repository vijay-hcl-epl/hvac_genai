#ifndef FEEDBACK_ADC_H
#define FEEDBACK_ADC_H
#include <stdint.h>
void Feedback_Init(void);
void Feedback_PeriodicTask(void);
uint8_t Feedback_GetPosition(void);
uint8_t Feedback_IsValid(void);
#endif /* FEEDBACK_ADC_H */
