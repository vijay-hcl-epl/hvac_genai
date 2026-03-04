#ifndef POSITION_CTRL_LOGIC_H
#define POSITION_CTRL_LOGIC_H

#include <stdint.h>

/** Movement state machine for position logic */
typedef enum {
    CTRL_STATE_IDLE,
    CTRL_STATE_MOVING_FWD,
    CTRL_STATE_MOVING_REV,
    CTRL_STATE_HOLD,
    CTRL_STATE_ERROR
} ctrl_state_t;

/** Set target position from command handler */
void ctrl_logic_set_target(int pos);

/** Update with most recent measured position */
void ctrl_logic_update_feedback(int pos);

/** Get current movement state. */
int ctrl_logic_get_state(void);

/** Reset movement logic state machine. */
void ctrl_logic_reset(void);

#endif // POSITION_CTRL_LOGIC_H
