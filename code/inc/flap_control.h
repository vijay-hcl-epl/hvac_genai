#ifndef FLAP_CONTROL_H
#define FLAP_CONTROL_H

#include <stdint.h>
#include <stdbool.h>
#include "feedback_processor.h"

#define FLAP_POS_MIN 0x00U
#define FLAP_POS_MAX 0xE0U

typedef enum {
    FLAP_IDLE = 0,
    FLAP_MOVING,
    FLAP_TARGET_REACHED,
    FLAP_FAULT
} flap_state_t;

typedef struct {
    uint8_t current_position;
    uint8_t target_position;
    bool in_motion;
    flap_state_t state;
} flap_control_t;

void flap_control_init(flap_control_t *inst, uint8_t cur_pos);
bool flap_control_update(flap_control_t *inst, uint8_t cmd_pos, bool cmd_valid, uint8_t fb_pos, bool fb_valid);

#endif /* FLAP_CONTROL_H */
