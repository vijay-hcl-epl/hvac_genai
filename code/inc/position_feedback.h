#ifndef POSITION_FEEDBACK_H
#define POSITION_FEEDBACK_H

#include <stdbool.h>
#include <stdint.h>

void PositionFeedback_Init(void);
bool PositionFeedback_GetPosition(uint8_t *pos);
bool PositionFeedback_IsValid(void);
void PositionFeedback_SampleADC(void);

#endif // POSITION_FEEDBACK_H
