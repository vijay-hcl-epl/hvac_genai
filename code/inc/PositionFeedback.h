#ifndef POSITION_FEEDBACK_H
#define POSITION_FEEDBACK_H
#include <stdint.h>
#include <stdbool.h>

void PositionFeedback_Init(void);
void PositionFeedback_TriggerSample(void);
bool PositionFeedback_GetPosition(uint8_t *pos);

#endif // POSITION_FEEDBACK_H
