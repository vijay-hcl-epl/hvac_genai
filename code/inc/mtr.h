#ifndef MTR_H
#define MTR_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    MTR_STATE_IDLE=0,
    MTR_STATE_MOVING_FWD,
    MTR_STATE_MOVING_REV,
    MTR_STATE_ERROR_STOP
} mtr_state_t;

void mtr_init(void);
void mtr_set_target_position(int target);
void mtr_force_idle(void);
mtr_state_t mtr_get_state(void);

#endif // MTR_H
