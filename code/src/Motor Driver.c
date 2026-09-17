#include "Motor Driver.h"
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim3;

#define MOTOR_PWM_CHANNEL             TIM_CHANNEL_1
#define MOTOR_PWM_DUTY_RUN            (600U)
#define MOTOR_PWM_DUTY_STOP           (0U)
#define MOTOR_ENABLED                 (1U)
#define MOTOR_DISABLED                (0U)

static Motor_Status_t motor_status;

static void Motor_Driver_Set_Direction(Motor_Direction_t direction)
{
    if (direction == MOTOR_DIRECTION_OPEN)
    {
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
    }
    else if (direction == MOTOR_DIRECTION_CLOSE)
    {
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
    }
}

void Motor_Driver_Init(void)
{
    motor_status.direction = MOTOR_DIRECTION_STOP;
    motor_status.enabled = MOTOR_DISABLED;
    motor_status.duty = MOTOR_PWM_DUTY_STOP;
    (void)HAL_TIM_PWM_Start(&htim3, MOTOR_PWM_CHANNEL);
    Motor_Driver_Stop();
}

void Motor_Driver_Drive(Motor_Direction_t direction, uint8_t enable)
{
    if ((enable != 0U) && (direction != MOTOR_DIRECTION_STOP))
    {
        Motor_Driver_Set_Direction(direction);
        __HAL_TIM_SET_COMPARE(&htim3, MOTOR_PWM_CHANNEL, MOTOR_PWM_DUTY_RUN);
        motor_status.direction = direction;
        motor_status.enabled = MOTOR_ENABLED;
        motor_status.duty = MOTOR_PWM_DUTY_RUN;
    }
    else
    {
        Motor_Driver_Stop();
    }
}

void Motor_Driver_Stop(void)
{
    Motor_Driver_Set_Direction(MOTOR_DIRECTION_STOP);
    __HAL_TIM_SET_COMPARE(&htim3, MOTOR_PWM_CHANNEL, MOTOR_PWM_DUTY_STOP);
    motor_status.direction = MOTOR_DIRECTION_STOP;
    motor_status.enabled = MOTOR_DISABLED;
    motor_status.duty = MOTOR_PWM_DUTY_STOP;
}

Motor_Status_t Motor_Driver_Get_Status(void)
{
    return motor_status;
}
