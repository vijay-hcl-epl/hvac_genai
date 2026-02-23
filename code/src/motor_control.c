#include "motor_control.h"
#include "stm32f4xx_hal.h"

#define MOTOR_DIR_PIN1 GPIO_PIN_8 // PB8 example
#define MOTOR_DIR_PIN2 GPIO_PIN_9 // PB9 example
#define MOTOR_PORT GPIOB
extern TIM_HandleTypeDef htim3; // configured for PWM

void MOTOR_Init(void)
{
    // assumed pin setup elsewhere using STM32Cube
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
}

void MOTOR_Run(MotorDir dir)
{
    if (dir == MOTOR_DIR_CW)
    {
        HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_DIR_PIN1, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_DIR_PIN2, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_DIR_PIN1, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_DIR_PIN2, GPIO_PIN_SET);
    }
    // Enable PWM - set duty for speed if needed
}

void MOTOR_Stop(void)
{
    HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_DIR_PIN1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_DIR_PIN2, GPIO_PIN_RESET);
}
