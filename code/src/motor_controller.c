#include "motor_controller.h"
#include <stdint.h>
#include <stdbool.h>
// Hardware stub. Replace with actual GPIO and PWM calls.
typedef enum { MC_OFF, MC_MOVING } MotorState;

static MotorState mc_state = MC_OFF;

static void motor_hw_set_dir_cw(void) {
    // set GPIOs for CW
}
static void motor_hw_set_dir_ccw(void) {
    // set GPIOs for CCW
}
static void motor_hw_enable_pwm(void) {
    // enable PWM (e.g., set duty cycle)
}
static void motor_hw_disable_pwm(void) {
    // disable PWM (duty 0, EN low)
}

void motor_set(uint8_t target, uint8_t current, bool valid) {
    if (!valid || target == current) {
        motor_stop();
        mc_state = MC_OFF;
        return;
    }
    if (target > current) {
        motor_hw_set_dir_cw();
        motor_hw_enable_pwm();
    } else {
        motor_hw_set_dir_ccw();
        motor_hw_enable_pwm();
    }
    mc_state = MC_MOVING;
}
void motor_stop(void) {
    motor_hw_disable_pwm();
    mc_state = MC_OFF;
}
