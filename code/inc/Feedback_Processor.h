#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>

#define FEEDBACK_POS_INVALID    (0xFFU)

void Feedback_Processor_Init(void);
void Feedback_Processor_Update(void);
uint8_t Feedback_Processor_Get_Position(void);
bool Feedback_Processor_Is_Valid(void);

#endif // FEEDBACK_PROCESSOR_H
