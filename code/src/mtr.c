#include "mtr.h"
#include "pos.h"
#include <stdint.h>

static int target_pos = -1;
static mtr_state_t mtr_state = MTR_STATE_IDLE;
static bool safe_state = false;

static void set_motor_gpio_pwm(bool enable, bool dir_fwd) {
    // Hardware stub
    (void)enable; (void)dir_fwd;
}

void mtr_init(void) {
    target_pos = -1;
    mtr_state = MTR_STATE_IDLE;
    safe_state = false;
}

void mtr_set_target_position(int target) {
    target_pos = target;
}

void mtr_force_idle(void) {
    set_motor_gpio_pwm(false, false);
    mtr_state = MTR_STATE_IDLE;
}

mtr_state_t mtr_get_state(void) {
    return mtr_state;
}

void mtr_task_step(void) {
    if (safe_state) {
        set_motor_gpio_pwm(false, false);
        mtr_state = MTR_STATE_ERROR_STOP;
        return;
    }
    int cur;
    if (!pos_get_current_position(&cur)) {
        mtr_force_idle();
        mtr_state = MTR_STATE_ERROR_STOP;
        return;
    }
    if (target_pos < 0 || target_pos > 5) {
        mtr_force_idle();
        mtr_state = MTR_STATE_IDLE;
        return;
    }
    if (cur == target_pos) {
        set_motor_gpio_pwm(false, false);
        mtr_state = MTR_STATE_IDLE;
    } else if (cur < target_pos) {
        set_motor_gpio_pwm(true, true);
        mtr_state = MTR_STATE_MOVING_FWD;
    } else {
        set_motor_gpio_pwm(true, false);
        mtr_state = MTR_STATE_MOVING_REV;
    }
}

// Call this from SUPV to update safe state
void mtr_set_safe_state(bool state) {
    safe_state = state;
    if (state) mtr_force_idle();
}
