#ifndef STATUS_INDICATOR_H
#define STATUS_INDICATOR_H

#include <stdbool.h>
#include <stdint.h>

void StatusIndicator_Init(void);
void StatusIndicator_Update(uint8_t logical_position, bool powered);

#endif // STATUS_INDICATOR_H
