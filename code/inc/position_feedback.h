#ifndef POSITION_FEEDBACK_H
#define POSITION_FEEDBACK_H

#include <stdbool.h>

void PositionFeedback_Init(void);
void PositionFeedback_Sample(void); // to be called periodically
int PositionFeedback_GetPosition(void);
bool PositionFeedback_IsValid(void);
bool PositionFeedback_IsPositionValid(int position);

#endif // POSITION_FEEDBACK_H
