#ifndef STATUS_LED_INDICATION_H
#define STATUS_LED_INDICATION_H

#include <stdint.h>

/** Update LED status based on position/error. */
void led_indication_update(int pos, int error);

/** Indicate error status/pattern. */
void led_indication_error(void);

#endif // STATUS_LED_INDICATION_H
