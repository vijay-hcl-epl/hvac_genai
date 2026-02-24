#include "motor_control.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>

// GPIO & PWM pin/port definitions (Assume these symbolic names are defined by CubeMX or board support)
#define MOTOR_IN1_PORT GPIOB
#define MOTOR_IN1_PIN  GPIO_PIN_0
#define MOTOR_IN2_PORT GPIOB
#define MOTOR_IN2_PIN  GPIO_PIN_1
#define MOTOR_EN_PORT  GPIOB
#define MOTOR_EN_PIN   GPIO_PIN_10
#define MOTOR_PWM_TIM  htim2
#define MOTOR_PWM_CHNL TIM_CHANNEL_3

static ControlOrder_t last_order = CTRL_ORDER_STOP;

void MotorControl_Init(void)
{
    // User should initialize relevant GPIOs and PWM in board setup.
    last_order = CTRL_ORDER_STOP;
}

void MotorControl_ApplyOrder(ControlOrder_t order)
{
    if (order == last_order) return;
    last_order = order;
    switch (order)
    {
    case CTRL_ORDER_STOP:
        HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_EN_PORT, MOTOR_EN_PIN, GPIO_PIN_RESET);
        HAL_TIM_PWM_Stop(&MOTOR_PWM_TIM, MOTOR_PWM_CHNL);
        break;
    case CTRL_ORDER_MOVE_CW:
        HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_EN_PORT, MOTOR_EN_PIN, GPIO_PIN_SET);
        HAL_TIM_PWM_Start(&MOTOR_PWM_TIM, MOTOR_PWM_CHNL);
        break;
    case CTRL_ORDER_MOVE_CCW:
        HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_EN_PORT, MOTOR_EN_PIN, GPIO_PIN_SET);
        HAL_TIM_PWM_Start(&MOTOR_PWM_TIM, MOTOR_PWM_CHNL);
        break;
    default:
        HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_EN_PORT, MOTOR_EN_PIN, GPIO_PIN_RESET);
        HAL_TIM_PWM_Stop(&MOTOR_PWM_TIM, MOTOR_PWM_CHNL);
        break;
    }
}
