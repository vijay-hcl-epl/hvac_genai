#ifndef STATUS_INDICATION_H
#define STATUS_INDICATION_H

#include <stdint.h>

void SetLEDs(uint8_t state_code);
void UpdateStatusIndicator(void);

#endif // STATUS_INDICATION_H
