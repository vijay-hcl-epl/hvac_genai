/**
 * @file motor_driver.c
 * @brief Motor Driver implementation – DC motor GPIO/PWM actuation via L298N.
 *
 * Software Unit: Motor Driver
 * Traces: SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025, SWE-REQ-036, SWE-REQ-038
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL
 *
 * L298N Interface Pin Mapping (configurable):
 *   IN1 (Direction A) : PB0  (GPIO output)
 *   IN2 (Direction B) : PB1  (GPIO output)
 *   ENA (PWM Enable)  : PA0  (TIM2_CH1 PWM output)
 */

#include "motor_driver.h"
#include "stm32f4xx_hal.h"

/* ---------- Pin definitions [SWE-REQ-038] ---------- */

#define MOTOR_IN1_PORT      GPIOB
#define MOTOR_IN1_PIN       GPIO_PIN_0

#define MOTOR_IN2_PORT      GPIOB
#define MOTOR_IN2_PIN       GPIO_PIN_1

/* External timer handle for PWM (TIM2 CH1, defined in system_init.c) */
extern TIM_HandleTypeDef htim2;

/** PWM timer channel used for motor enable */
#define MOTOR_PWM_CHANNEL   TIM_CHANNEL_1

/* ---------- Static (file-scope) data [SWE-REQ-009, SWE-REQ-036] ---------- */

/** Current motor status */
static MotorStatus_t s_MotorStatus = MOTOR_STATUS_IDLE;

/** Current direction stored for status reporting */
static MotorDirection_t s_CurrentDirection = MOTOR_DIR_STOP;

/* ---------- Internal helpers -------------------------------------------- */

/**
 * @brief Set PWM duty cycle (0..100%).
 * @param duty  Duty cycle percentage.
 */
static void MotorDriver_SetPwmDuty(uint8_t duty)
{
    uint32_t period;
    uint32_t pulse;

    period = __HAL_TIM_GET_AUTORELOAD(&htim2);
    pulse  = (uint32_t)(((uint32_t)duty * (period + 1U)) / 100U);

    __HAL_TIM_SET_COMPARE(&htim2, MOTOR_PWM_CHANNEL, pulse);
}

/* ---------- Public API -------------------------------------------------- */

void MotorDriver_Init(void)
{
    /* Ensure motor is OFF on init (safe state) [SWE-REQ-020] */
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);

    /* Start PWM with 0% duty */
    HAL_TIM_PWM_Start(&htim2, MOTOR_PWM_CHANNEL);
    MotorDriver_SetPwmDuty(0U);

    s_MotorStatus     = MOTOR_STATUS_IDLE;
    s_CurrentDirection = MOTOR_DIR_STOP;
}

void MotorDriver_Drive(MotorDirection_t dir, bool enable)
{
    if (enable == false)
    {
        /* Coast-stop: disable PWM, clear direction pins */
        MotorDriver_SetPwmDuty(0U);
        HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
        s_MotorStatus     = MOTOR_STATUS_IDLE;
        s_CurrentDirection = MOTOR_DIR_STOP;
    }
    else
    {
        switch (dir)
        {
            case MOTOR_DIR_FORWARD:
                /* IN1 = HIGH, IN2 = LOW [SWE-REQ-007] */
                HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_SET);
                HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
                MotorDriver_SetPwmDuty(MOTOR_DEFAULT_PWM_DUTY);
                s_MotorStatus     = MOTOR_STATUS_RUNNING;
                s_CurrentDirection = MOTOR_DIR_FORWARD;
                break;

            case MOTOR_DIR_REVERSE:
                /* IN1 = LOW, IN2 = HIGH [SWE-REQ-007] */
                HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_SET);
                MotorDriver_SetPwmDuty(MOTOR_DEFAULT_PWM_DUTY);
                s_MotorStatus     = MOTOR_STATUS_RUNNING;
                s_CurrentDirection = MOTOR_DIR_REVERSE;
                break;

            case MOTOR_DIR_STOP:
                /* Fall through to stop */
                MotorDriver_Stop();
                break;

            default:
                /* Unknown direction – safe stop [SWE-REQ-025] */
                MotorDriver_Stop();
                break;
        }
    }
}

void MotorDriver_Stop(void)
{
    /* Immediately cease all motor output (safe state) [SWE-REQ-008, SWE-REQ-025] */
    MotorDriver_SetPwmDuty(0U);
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
    s_MotorStatus     = MOTOR_STATUS_IDLE;
    s_CurrentDirection = MOTOR_DIR_STOP;
}

MotorStatus_t MotorDriver_GetStatus(void)
{
    return s_MotorStatus;
}
