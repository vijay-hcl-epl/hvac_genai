#ifndef FLAP_MONITOR_H
#define FLAP_MONITOR_H

#include <stdint.h>

void update_flap_feedback(int8_t new_position);
int8_t get_current_flap_feedback(void);

#endif // FLAP_MONITOR_H
