#ifndef POSITION_FEEDBACK_H
#define POSITION_FEEDBACK_H
#include <stdint.h>
void PositionFeedback_Init(void);
void PositionFeedback_Process(void);
uint8_t PositionFeedback_GetPosition(void);
#endif
