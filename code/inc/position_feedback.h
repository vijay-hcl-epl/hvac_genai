#ifndef POSITION_FEEDBACK_H
#define POSITION_FEEDBACK_H
#include <stdint.h>
void PositionFeedback_Init(void);
uint8_t GetCurrentFlapPosition(void);
void PositionFeedback_AdcInterruptHandler(uint16_t adc_value);
#endif // POSITION_FEEDBACK_H
