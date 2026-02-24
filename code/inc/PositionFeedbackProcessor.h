#ifndef POSITION_FEEDBACK_PROCESSOR_H
#define POSITION_FEEDBACK_PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>

// Position Feedback Processor APIs
void PosFb_Processor_Init(void);
void PosFb_Processor_TriggerSample(void);
int8_t PosFb_Processor_GetPosition(void);
bool PosFb_Processor_IsOutOfRange(void);

#endif // POSITION_FEEDBACK_PROCESSOR_H
