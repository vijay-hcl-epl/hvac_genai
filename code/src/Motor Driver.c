#include "Motor Driver.h"
#include "stm32f4xx_hal.h"

/* L298N DC motor control using GPIO direction and timer PWM enable.
 * Traces: SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025, SWE-REQ-036, SWE-REQ-038.
 */

#define MOTOR_DRIVER_IN1_GPIO_PORT      GPIOB
#define MOTOR_DRIVER_IN1_GPIO_PIN       GPIO_PIN_0
#define MOTOR_DRIVER_IN2_GPIO_PORT      GPIOB
#define MOTOR_DRIVER_IN2_GPIO_PIN       GPIO_PIN_1
#define MOTOR_DRIVER_PWM_CHANNEL        TIM_CHANNEL_1
#define MOTOR_DRIVER_PWM_DUTY_ACTIVE    700U
#define MOTOR_DRIVER_PWM_DUTY_STOP      0U

extern TIM_HandleTypeDef htim3;

static MotorDriver_Status_t MotorDriver_Status =
{
    false,
    MOTOR_DRIVER_DIRECTION_STOP,
    MOTOR_DRIVER_PWM_DUTY_STOP
};

static void MotorDriver_ApplyPwm(uint16_t duty)
{
    __HAL_TIM_SET_COMPARE(&htim3, MOTOR_DRIVER_PWM_CHANNEL, (uint32_t)duty);
}

void MotorDriver_Init(void)
{
    (void)HAL_TIM_PWM_Start(&htim3, MOTOR_DRIVER_PWM_CHANNEL);
    MotorDriver_StopMotor();
}

void MotorDriver_DriveMotor(MotorDriver_Direction_t dir, bool enable)
{
    if ((enable == false) || (dir == MOTOR_DRIVER_DIRECTION_STOP))
    {
        MotorDriver_StopMotor();
    }
    else
    {
        if (dir == MOTOR_DRIVER_DIRECTION_FORWARD)
        {
            HAL_GPIO_WritePin(MOTOR_DRIVER_IN1_GPIO_PORT, MOTOR_DRIVER_IN1_GPIO_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR_DRIVER_IN2_GPIO_PORT, MOTOR_DRIVER_IN2_GPIO_PIN, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(MOTOR_DRIVER_IN1_GPIO_PORT, MOTOR_DRIVER_IN1_GPIO_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_DRIVER_IN2_GPIO_PORT, MOTOR_DRIVER_IN2_GPIO_PIN, GPIO_PIN_SET);
        }

        MotorDriver_ApplyPwm(MOTOR_DRIVER_PWM_DUTY_ACTIVE);
        MotorDriver_Status.enabled = true;
        MotorDriver_Status.direction = dir;
        MotorDriver_Status.pwm_duty = MOTOR_DRIVER_PWM_DUTY_ACTIVE;
    }
}

void MotorDriver_StopMotor(void)
{
    HAL_GPIO_WritePin(MOTOR_DRIVER_IN1_GPIO_PORT, MOTOR_DRIVER_IN1_GPIO_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_DRIVER_IN2_GPIO_PORT, MOTOR_DRIVER_IN2_GPIO_PIN, GPIO_PIN_RESET);
    MotorDriver_ApplyPwm(MOTOR_DRIVER_PWM_DUTY_STOP);
    MotorDriver_Status.enabled = false;
    MotorDriver_Status.direction = MOTOR_DRIVER_DIRECTION_STOP;
    MotorDriver_Status.pwm_duty = MOTOR_DRIVER_PWM_DUTY_STOP;
}

MotorDriver_Status_t MotorDriver_GetStatus(void)
{
    return MotorDriver_Status;
}
