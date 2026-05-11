#ifndef INDICATOR_CONTROL_H
#define INDICATOR_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {IDLE, MOVING, ERROR} system_state_t;

void indicator_control_init(void);
void indicator_control_update(system_state_t state, uint8_t logical_pos, bool moving);

#endif // INDICATOR_CONTROL_H
