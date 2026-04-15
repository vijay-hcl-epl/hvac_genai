#include "MotorDriver.h"
#include "stm32f4xx_hal.h"

#define MOTOR_EN_GPIO_PORT GPIOA
#define MOTOR_EN_PIN GPIO_PIN_8
#define MOTOR_IN1_PORT GPIOA
#define MOTOR_IN1_PIN GPIO_PIN_9
#define MOTOR_IN2_PORT GPIOA
#define MOTOR_IN2_PIN GPIO_PIN_10
extern TIM_HandleTypeDef htim1;

static bool motor_running = false;

void MotorDriver_Init(void) {
    HAL_GPIO_WritePin(MOTOR_EN_GPIO_PORT, MOTOR_EN_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
    motor_running = false;
}

void MotorDriver_Drive(MotorDriver_Direction_t dir, uint8_t pwm) {
    if (dir == MOTOR_DIR_STOP) {
        MotorDriver_Stop();
        return;
    }
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, dir == MOTOR_DIR_FORWARD ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, dir == MOTOR_DIR_REVERSE ? GPIO_PIN_SET : GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm);
    HAL_GPIO_WritePin(MOTOR_EN_GPIO_PORT, MOTOR_EN_PIN, GPIO_PIN_SET);
    motor_running = true;
}

void MotorDriver_Stop(void) {
    HAL_GPIO_WritePin(MOTOR_EN_GPIO_PORT, MOTOR_EN_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    motor_running = false;
}

bool MotorDriver_GetStatus(void) {
    return motor_running;
}
