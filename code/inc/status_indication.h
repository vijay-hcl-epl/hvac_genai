#ifndef STATUS_INDICATION_H
#define STATUS_INDICATION_H

#include <stdint.h>

void status_indication_init(void);
void update_indicators(uint8_t state_flags);
void indicate_power_on(void);
void indicate_position(unsigned int logical_position);
void indicate_error(bool error_active);

#endif // STATUS_INDICATION_H
