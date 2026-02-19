#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H
#include <stdint.h>

typedef enum {
    FLAP_IDLE = 0,
    FLAP_MOVING,
    FLAP_TARGET_REACHED,
    FLAP_ERROR
} flap_state_t;

void flap_control_logic_init(void);
void flap_control_logic_update_target(uint16_t tgt_position);
flap_state_t flap_control_logic_get_state(void);
void flap_control_logic_periodic(void);

#endif // FLAP_CONTROL_LOGIC_H
