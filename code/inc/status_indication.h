#ifndef STATUS_INDICATION_H
#define STATUS_INDICATION_H

#include <stdint.h>
#include <stdbool.h>

void status_indication_init(void);
void status_indication_update_leds(bool power_on, uint8_t pos_idx);

#endif // STATUS_INDICATION_H
