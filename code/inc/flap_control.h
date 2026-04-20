#ifndef FLAP_CONTROL_H
#define FLAP_CONTROL_H
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    FLAP_IDLE = 0,
    FLAP_MOVING,
    FLAP_ERROR
} flap_state_t;

void request_flap_move(uint8_t pos);
void feedback_update(uint8_t sensed_pos, bool errorflag);

#endif // FLAP_CONTROL_H
