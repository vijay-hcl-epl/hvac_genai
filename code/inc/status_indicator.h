#ifndef STATUS_INDICATOR_H
#define STATUS_INDICATOR_H
#include <stdint.h>
void StatusLED_set(uint8_t pos);
void PowerLED_on(void);
void status_indicator_init(void);
#endif // STATUS_INDICATOR_H
