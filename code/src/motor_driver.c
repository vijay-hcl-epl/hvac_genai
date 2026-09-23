/**
 * @file    motor_driver.c
 * @brief   Motor Driver software unit – implementation.
 *
 * Interfaces with L298N H-Bridge via GPIO (direction) and
 * PWM / Timer (enable / speed).
 *
 * Traceability:
 *   SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025, SWE-REQ-032,
 *   SWE-REQ-036, SWE-REQ-038.
 *
 * @note    Platform: STM32F407G-DISC1, STM32 HAL, L298N.
 *
 * Pin Mapping (L298N ↔ STM32):
 *   IN1 (direction A) : PB4  (GPIO output)
 *   IN2 (direction B) : PB5  (GPIO output)
 *   ENA (PWM enable)  : PA6  (TIM3 CH1 – PWM output)
 */

/* ---- Includes ------------------------------------------------------- */
#include "motor_driver.h"
#include "stm32f4xx_hal.h"

/* ---- Extern HAL Handle ---------------------------------------------- */
extern TIM_HandleTypeDef htim3;

/* ---- Private Constants / Pin Map (SWE-REQ-016, SWE-REQ-038) -------- */

#define MOTOR_IN1_PORT     GPIOB
#define MOTOR_IN1_PIN      GPIO_PIN_4

#define MOTOR_IN2_PORT     GPIOB
#define MOTOR_IN2_PIN      GPIO_PIN_5

/** @brief PWM timer channel for ENA. */
#define MOTOR_PWM_CHANNEL  TIM_CHANNEL_1

/** @brief Timer auto-reload value (set during init). */
#define MOTOR_PWM_PERIOD   (999U)

/* ---- Static Data (SWE-REQ-036) ------------------------------------- */

static MotorStatus_t s_motorStatus;

/* ---- Public API Implementation -------------------------------------- */

/* [SWE-REQ-020, SWE-REQ-008] */
void MotorDriver_Init(void)
{
    /* Ensure direction pins LOW (motor coast). */
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);

    /* PWM duty = 0 (stopped). */
    __HAL_TIM_SET_COMPARE(&htim3, MOTOR_PWM_CHANNEL, 0U);
    HAL_TIM_PWM_Start(&htim3, MOTOR_PWM_CHANNEL);

    s_motorStatus = MOTOR_STATUS_STOPPED;
}

/* [SWE-REQ-007, SWE-REQ-016] */
void MotorDriver_Drive(MotorDirection_t dir, bool enable)
{
    if (enable == true)
    {
        if (dir == MOTOR_DIR_CW)
        {
            HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
        }
        else /* MOTOR_DIR_CCW */
        {
            HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_SET);
        }

        /* Set PWM duty for speed (SWE-REQ-035 configurable param). */
        uint32_t duty = ((uint32_t)(MOTOR_PWM_PERIOD + 1U) *
                         (uint32_t)MOTOR_DEFAULT_DUTY_PERCENT) / 100U;
        __HAL_TIM_SET_COMPARE(&htim3, MOTOR_PWM_CHANNEL, duty);

        s_motorStatus = MOTOR_STATUS_RUNNING;
    }
    else
    {
        MotorDriver_Stop();
    }
}

/* [SWE-REQ-008, SWE-REQ-025, SWE-REQ-032] */
void MotorDriver_Stop(void)
{
    /* All outputs OFF – safe state. */
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(&htim3, MOTOR_PWM_CHANNEL, 0U);

    s_motorStatus = MOTOR_STATUS_STOPPED;
}

/* [SWE-REQ-040] */
MotorStatus_t MotorDriver_GetStatus(void)
{
    return s_motorStatus;
}
