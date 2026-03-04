/* StatusIndicator.h - Control status LED and position indication LEDs. */
#ifndef STATUS_INDICATOR_H
#define STATUS_INDICATOR_H

#include <stdint.h>

void StatusIndicator_Init(void);
void StatusIndicator_Update(uint8_t position);
void StatusIndicator_ShowError(void);

#endif /* STATUS_INDICATOR_H */
