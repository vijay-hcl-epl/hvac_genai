#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdbool.h>
#include <stdint.h>

void Feedback_Processor_Init(void);
void Feedback_Processor_Update(void);
bool Feedback_Processor_GetPosition(uint8_t * position);
uint16_t Feedback_Processor_GetLatestAdc(void);

#endif /* FEEDBACK_PROCESSOR_H */
