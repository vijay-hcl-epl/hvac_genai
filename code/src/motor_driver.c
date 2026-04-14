#include "motor_driver.h"
#include "main.h" // For HAL handles
#include "stm32f4xx_hal.h" // For HAL GPIO/PWM

static motor_dir_t last_dir = MOTOR_DIR_FWD;
static bool enabled = false;

void motor_init(void) {
    enabled = false;
    last_dir = MOTOR_DIR_FWD;
    // Initialize hardware pins/timers in MX_GPIO_Init/MX_TIMx_Init
    motor_stop();
}

void motor_drive(motor_dir_t dir, bool enable) {
    last_dir = dir;
    enabled = enable;
    // GPIO direction
    HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, (dir == MOTOR_DIR_FWD) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    // PWM enable
    if (enable) {
        HAL_TIM_PWM_Start(&htimx, TIM_CHANNEL_x); // fill correct TIM handle/channel
    } else {
        HAL_TIM_PWM_Stop(&htimx, TIM_CHANNEL_x);
    }
}

void motor_stop(void) {
    enabled = false;
    HAL_TIM_PWM_Stop(&htimx, TIM_CHANNEL_x);
    // Optionally set enable GPIO low if needed
}

bool motor_get_status(void) {
    return enabled;
}
