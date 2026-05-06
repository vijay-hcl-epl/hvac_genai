#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>

#define FEEDBACK_POSITION_INVALID 0xFFu
#define FEEDBACK_POSITION_COUNT 5

// Mapping table for ADC -> Logical Position
extern const uint16_t FeedbackProcessor_ADCThresholds[FEEDBACK_POSITION_COUNT+1];

void FeedbackProcessor_Init(void);
void FeedbackProcessor_Update(void);
bool FeedbackProcessor_GetPosition(uint8_t* position);
bool FeedbackProcessor_IsFeedbackValid(void);

#endif // FEEDBACK_PROCESSOR_H
