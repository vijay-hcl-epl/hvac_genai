#include "Motor Driver.h"
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim4;

#ifndef HVAC_MOTOR_IN1_PORT
#define HVAC_MOTOR_IN1_PORT GPIOE
#endif
#ifndef HVAC_MOTOR_IN1_PIN
#define HVAC_MOTOR_IN1_PIN GPIO_PIN_0
#endif
#ifndef HVAC_MOTOR_IN2_PORT
#define HVAC_MOTOR_IN2_PORT GPIOE
#endif
#ifndef HVAC_MOTOR_IN2_PIN
#define HVAC_MOTOR_IN2_PIN GPIO_PIN_1
#endif
#ifndef HVAC_MOTOR_PWM_CHANNEL
#define HVAC_MOTOR_PWM_CHANNEL TIM_CHANNEL_1
#endif

#define MOTOR_DRIVER_PWM_STOP_DUTY (0U)
#define MOTOR_DRIVER_PWM_RUN_DUTY  (600U)

static Motor_Driver_StatusType Motor_Driver_Status =
{
    MOTOR_DRIVER_DIR_STOP,
    false,
    MOTOR_DRIVER_PWM_STOP_DUTY
};

void Motor_Driver_Init(void)
{
    Motor_Driver_StopMotor();
}

void Motor_Driver_DriveMotor(uint8_t direction, bool enable)
{
    if ((enable == false) || (direction == MOTOR_DRIVER_DIR_STOP))
    {
        Motor_Driver_StopMotor();
    }
    else if (direction == MOTOR_DRIVER_DIR_OPEN)
    {
        HAL_GPIO_WritePin(HVAC_MOTOR_IN1_PORT, HVAC_MOTOR_IN1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(HVAC_MOTOR_IN2_PORT, HVAC_MOTOR_IN2_PIN, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim4, HVAC_MOTOR_PWM_CHANNEL, MOTOR_DRIVER_PWM_RUN_DUTY);
        (void)HAL_TIM_PWM_Start(&htim4, HVAC_MOTOR_PWM_CHANNEL);
        Motor_Driver_Status.direction = MOTOR_DRIVER_DIR_OPEN;
        Motor_Driver_Status.enabled = true;
        Motor_Driver_Status.pwm_duty = MOTOR_DRIVER_PWM_RUN_DUTY;
    }
    else if (direction == MOTOR_DRIVER_DIR_CLOSE)
    {
        HAL_GPIO_WritePin(HVAC_MOTOR_IN1_PORT, HVAC_MOTOR_IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(HVAC_MOTOR_IN2_PORT, HVAC_MOTOR_IN2_PIN, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim4, HVAC_MOTOR_PWM_CHANNEL, MOTOR_DRIVER_PWM_RUN_DUTY);
        (void)HAL_TIM_PWM_Start(&htim4, HVAC_MOTOR_PWM_CHANNEL);
        Motor_Driver_Status.direction = MOTOR_DRIVER_DIR_CLOSE;
        Motor_Driver_Status.enabled = true;
        Motor_Driver_Status.pwm_duty = MOTOR_DRIVER_PWM_RUN_DUTY;
    }
    else
    {
        Motor_Driver_StopMotor();
    }
}

void Motor_Driver_StopMotor(void)
{
    HAL_GPIO_WritePin(HVAC_MOTOR_IN1_PORT, HVAC_MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(HVAC_MOTOR_IN2_PORT, HVAC_MOTOR_IN2_PIN, GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(&htim4, HVAC_MOTOR_PWM_CHANNEL, MOTOR_DRIVER_PWM_STOP_DUTY);
    (void)HAL_TIM_PWM_Stop(&htim4, HVAC_MOTOR_PWM_CHANNEL);
    Motor_Driver_Status.direction = MOTOR_DRIVER_DIR_STOP;
    Motor_Driver_Status.enabled = false;
    Motor_Driver_Status.pwm_duty = MOTOR_DRIVER_PWM_STOP_DUTY;
}

Motor_Driver_StatusType Motor_Driver_GetStatus(void)
{
    return Motor_Driver_Status;
}
