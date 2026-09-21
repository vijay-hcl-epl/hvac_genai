#include "Motor_Driver.h"
#include "stm32f4xx_hal.h"

#define MOTOR_IN1_PORT GPIOB
#define MOTOR_IN1_PIN  GPIO_PIN_1
#define MOTOR_IN2_PORT GPIOB
#define MOTOR_IN2_PIN  GPIO_PIN_2
#define MOTOR_PWM_CHANNEL TIM_CHANNEL_1
#define MOTOR_DEFAULT_DUTY_PERCENT (60U)

extern TIM_HandleTypeDef htim3;

static MotorDriver_StatusType motor_status;

static void MotorDriver_SetPwmDuty(uint16_t duty_percent)
{
    uint32_t period;
    uint32_t compare;

    period = (uint32_t)__HAL_TIM_GET_AUTORELOAD(&htim3);
    compare = ((period + 1UL) * (uint32_t)duty_percent) / 100UL;
    __HAL_TIM_SET_COMPARE(&htim3, MOTOR_PWM_CHANNEL, compare);
}

void MotorDriver_Init(void)
{
    motor_status.direction = MOTOR_DRIVER_DIR_STOP;
    motor_status.enabled = 0U;
    motor_status.duty_percent = 0U;
    (void)HAL_TIM_PWM_Start(&htim3, MOTOR_PWM_CHANNEL);
    MotorDriver_StopMotor();
}

void MotorDriver_DriveMotor(uint8_t direction, uint8_t enable)
{
    if ((enable == 0U) || (direction == MOTOR_DRIVER_DIR_STOP))
    {
        MotorDriver_StopMotor();
    }
    else if (direction == MOTOR_DRIVER_DIR_FORWARD)
    {
        HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
        MotorDriver_SetPwmDuty(MOTOR_DEFAULT_DUTY_PERCENT);
        motor_status.direction = direction;
        motor_status.enabled = 1U;
        motor_status.duty_percent = MOTOR_DEFAULT_DUTY_PERCENT;
    }
    else if (direction == MOTOR_DRIVER_DIR_REVERSE)
    {
        HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_SET);
        MotorDriver_SetPwmDuty(MOTOR_DEFAULT_DUTY_PERCENT);
        motor_status.direction = direction;
        motor_status.enabled = 1U;
        motor_status.duty_percent = MOTOR_DEFAULT_DUTY_PERCENT;
    }
    else
    {
        MotorDriver_StopMotor();
    }
}

void MotorDriver_StopMotor(void)
{
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
    MotorDriver_SetPwmDuty(0U);
    motor_status.direction = MOTOR_DRIVER_DIR_STOP;
    motor_status.enabled = 0U;
    motor_status.duty_percent = 0U;
}

MotorDriver_StatusType MotorDriver_GetStatus(void)
{
    return motor_status;
}
