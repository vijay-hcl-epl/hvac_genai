/**
 * @file motor_driver.c
 * @brief Motor Driver implementation – L298N via STM32 GPIO + PWM.
 *
 * Traces: SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025, SWE-REQ-036, SWE-REQ-038
 *
 * L298N connections (STM32F407G-DISC1):
 *   IN1 : PB0  (direction A)
 *   IN2 : PB1  (direction B)
 *   ENA : PB4  (TIM3_CH1 PWM – speed/enable)
 */

#include "motor_driver.h"
#include "stm32f4xx_hal.h"

/* ---- Platform handles ---- */
extern TIM_HandleTypeDef htim3;

/* ---- Pin definitions [SWE-REQ-016] ---- */
#define MOTOR_IN1_PORT   GPIOB
#define MOTOR_IN1_PIN    GPIO_PIN_0
#define MOTOR_IN2_PORT   GPIOB
#define MOTOR_IN2_PIN    GPIO_PIN_1

/** PWM duty for full-speed enable (0..999 matching TIM3 period) */
#define MOTOR_PWM_DUTY_FULL   (800U)

/** PWM duty for stopped motor */
#define MOTOR_PWM_DUTY_OFF    (0U)

/* ---- Module static data [SWE-REQ-036, SWE-REQ-038] ---- */
static MotorStatus_t s_motorStatus;

/* ---- Private helpers ---- */

/**
 * @brief Set TIM3 CH1 compare value (PWM duty).
 * @param duty  0..999
 */
static void Motor_SetPwmDuty(uint16_t duty)
{
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (uint32_t)duty);
}

/* ---- Public API ---- */

void MotorDriver_Init(void)
{
    /* Ensure motor is off at startup [SWE-REQ-020] */
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
    Motor_SetPwmDuty(MOTOR_PWM_DUTY_OFF);

    /* Start PWM timer (duty = 0, so motor is off) */
    (void)HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

    s_motorStatus = MOTOR_STATUS_STOPPED;
}

void MotorDriver_Drive(MotorDir_t dir, uint8_t enable)
{
    if (enable == 0U)
    {
        /* Disable / coast */
        MotorDriver_Stop();
        return;
    }

    switch (dir)
    {
        case MOTOR_DIR_FORWARD:
            /* IN1=HIGH, IN2=LOW → forward [SWE-REQ-007] */
            HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
            Motor_SetPwmDuty(MOTOR_PWM_DUTY_FULL);
            s_motorStatus = MOTOR_STATUS_RUNNING;
            break;

        case MOTOR_DIR_REVERSE:
            /* IN1=LOW, IN2=HIGH → reverse [SWE-REQ-007] */
            HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_SET);
            Motor_SetPwmDuty(MOTOR_PWM_DUTY_FULL);
            s_motorStatus = MOTOR_STATUS_RUNNING;
            break;

        case MOTOR_DIR_STOP:
        default:
            MotorDriver_Stop();
            break;
    }
}

void MotorDriver_Stop(void)
{
    /* Safe state: all outputs off [SWE-REQ-008, SWE-REQ-025] */
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
    Motor_SetPwmDuty(MOTOR_PWM_DUTY_OFF);
    s_motorStatus = MOTOR_STATUS_STOPPED;
}

MotorStatus_t MotorDriver_GetStatus(void)
{
    return s_motorStatus;
}
