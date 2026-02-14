#ifndef POSFEEDBACK_H
#define POSFEEDBACK_H
#include <stdint.h>
#include <stdbool.h>
void PosFeedback_Init(void);
uint8_t PosFeedback_GetPosition(void);
bool PosFeedback_InRange(void);
#endif // POSFEEDBACK_H
