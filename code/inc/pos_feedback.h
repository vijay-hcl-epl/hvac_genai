#ifndef POS_FEEDBACK_H
#define POS_FEEDBACK_H

#include <stdint.h>
#include <stdbool.h>

#define FLAP_POS_INVALID   255U

void PosFeedback_Init(void);
void PosFeedback_Step(void);
uint8_t PosFeedback_GetPosition(void);
bool PosFeedback_IsValid(void);
uint16_t PosFeedback_GetRawADC(void);

#endif /* POS_FEEDBACK_H */
