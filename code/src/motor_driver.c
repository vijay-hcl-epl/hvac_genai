#include "motor_driver.h"
#include "stm32f4xx_hal.h"

#define MOTOR_PWM_CHANNEL TIM_CHANNEL_1
#define MOTOR_TIMER_HANDLE htim1
#define MOTOR_ENABLE_GPIO_Port GPIOA
#define MOTOR_ENABLE_Pin GPIO_PIN_1
#define MOTOR_DIR_GPIO_Port GPIOA
#define MOTOR_DIR_Pin GPIO_PIN_2

extern TIM_HandleTypeDef MOTOR_TIMER_HANDLE;

static bool motor_enabled = false;
static MotorDirection_t last_dir = MOTOR_DIR_STOP;

void motor_driver_init(void) {
    motor_enabled = false;
    last_dir = MOTOR_DIR_STOP;
    HAL_GPIO_WritePin(MOTOR_ENABLE_GPIO_Port, MOTOR_ENABLE_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, GPIO_PIN_RESET);
}

void motor_drive(MotorDirection_t dir, bool enable) {
    if (enable) {
        if (dir == MOTOR_DIR_OPEN) {
            HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, GPIO_PIN_SET);
        } else if (dir == MOTOR_DIR_CLOSE) {
            HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, GPIO_PIN_RESET);
        }
        HAL_GPIO_WritePin(MOTOR_ENABLE_GPIO_Port, MOTOR_ENABLE_Pin, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&MOTOR_TIMER_HANDLE, MOTOR_PWM_CHANNEL, 1000);
        motor_enabled = true;
        last_dir = dir;
    } else {
        motor_stop();
    }
}

void motor_stop(void) {
    HAL_GPIO_WritePin(MOTOR_ENABLE_GPIO_Port, MOTOR_ENABLE_Pin, GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(&MOTOR_TIMER_HANDLE, MOTOR_PWM_CHANNEL, 0);
    motor_enabled = false;
    last_dir = MOTOR_DIR_STOP;
}

bool motor_get_status(void) {
    return motor_enabled;
}
