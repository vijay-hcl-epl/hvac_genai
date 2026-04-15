#include "Motor_Driver.h"
#include "stm32f4xx_hal.h"

#define MOTOR_EN_GPIO_Port      GPIOB
#define MOTOR_EN_Pin           GPIO_PIN_0
#define MOTOR_DIR_GPIO_Port     GPIOB
#define MOTOR_DIR_Pin          GPIO_PIN_1
#define MOTOR_PWM_TIMER        htim3
#define MOTOR_PWM_CHANNEL      TIM_CHANNEL_1

extern TIM_HandleTypeDef MOTOR_PWM_TIMER;
static bool motor_active = false;

void Motor_Driver_Init(void)
{
    motor_active = false;
    HAL_GPIO_WritePin(MOTOR_EN_GPIO_Port, MOTOR_EN_Pin, GPIO_PIN_RESET); // Disable
    HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, GPIO_PIN_RESET); // Default dir
    HAL_TIM_PWM_Stop(&MOTOR_PWM_TIMER, MOTOR_PWM_CHANNEL);
}

void Motor_Driver_Drive(MotorDirection_t dir, bool enable)
{
    HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, (dir == MOTOR_FORWARD) ? GPIO_PIN_RESET : GPIO_PIN_SET);
    if(enable)
    {
        HAL_GPIO_WritePin(MOTOR_EN_GPIO_Port, MOTOR_EN_Pin, GPIO_PIN_SET);
        // Example - 75% duty
        __HAL_TIM_SET_COMPARE(&MOTOR_PWM_TIMER, MOTOR_PWM_CHANNEL, (__HAL_TIM_GET_AUTORELOAD(&MOTOR_PWM_TIMER) * 3) / 4);
        HAL_TIM_PWM_Start(&MOTOR_PWM_TIMER, MOTOR_PWM_CHANNEL);
        motor_active = true;
    }
    else
    {
        Motor_Driver_Stop();
    }
}

void Motor_Driver_Stop(void)
{
    HAL_GPIO_WritePin(MOTOR_EN_GPIO_Port, MOTOR_EN_Pin, GPIO_PIN_RESET);
    HAL_TIM_PWM_Stop(&MOTOR_PWM_TIMER, MOTOR_PWM_CHANNEL);
    motor_active = false;
}

bool Motor_Driver_Is_Active(void)
{
    return motor_active;
}
