#ifndef STATUS_INDICATOR_H
#define STATUS_INDICATOR_H
#include <stdint.h>
#include "SystemTypes.h"

void StatusIndicator_Init(void);
void StatusIndicator_SetStatus(StatusType type);
void StatusIndicator_SetPosition(uint8_t pos);

#endif // STATUS_INDICATOR_H
