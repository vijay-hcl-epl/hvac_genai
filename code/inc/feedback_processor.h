#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>

void FeedbackProcessor_Init(void);
void FeedbackProcessor_SampleAndUpdate(void);
uint8_t FeedbackProcessor_GetCurrentPosition(void);
bool FeedbackProcessor_IsPositionValid(void);

#endif // FEEDBACK_PROCESSOR_H
