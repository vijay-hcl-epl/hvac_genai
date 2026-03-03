#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    FLAP_STATE_IDLE = 0,
    FLAP_STATE_MOVING,
    FLAP_STATE_COMPLETE,
    FLAP_STATE_ERROR
} flap_state_t;

void flap_control_logic_init(void);
void flap_control_logic_process(void);

#endif // FLAP_CONTROL_LOGIC_H
