#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>

void Feedback_Processor_Init(void);
void Feedback_Processor_Update(void);
void Feedback_Processor_Get_Position(uint8_t * position, uint8_t * valid);
uint16_t Feedback_Processor_Get_Last_Adc(void);

#endif
