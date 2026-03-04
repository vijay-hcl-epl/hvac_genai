#ifndef POSITION_FEEDBACK_H
#define POSITION_FEEDBACK_H
#include <stdbool.h>
#include <stdint.h>
#include "SystemTypes.h"

void PositionFeedback_Sample(void);
enum FlapPosition PositionFeedback_GetPosition(void);
bool PositionFeedback_IsValid(void);

#endif // POSITION_FEEDBACK_H
