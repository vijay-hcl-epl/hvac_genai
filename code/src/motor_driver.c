/**
 * @file motor_driver.c
 * @brief Motor Driver implementation for L298N via STM32 HAL GPIO/PWM.
 *
 * Traces: SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025, SWE-REQ-036, SWE-REQ-038
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, L298N H-Bridge, bare-metal
 *
 * Pin mapping (configurable per hardware):
 *   IN1 (Direction A) : PB0
 *   IN2 (Direction B) : PB1
 *   ENA (PWM enable)  : PA0  (TIM2_CH1)
 */

#include "motor_driver.h"
#include "stm32f4xx_hal.h"

/* ---------- Hardware pin definitions (SWE-REQ-030, SWE-REQ-038) ---------- */

#define MOTOR_IN1_PORT   GPIOB
#define MOTOR_IN1_PIN    GPIO_PIN_0

#define MOTOR_IN2_PORT   GPIOB
#define MOTOR_IN2_PIN    GPIO_PIN_1

/* ---------- Extern timer handle (defined in system_init.c) ---------- */
extern TIM_HandleTypeDef htim2;

/* ---------- Static data (SWE-REQ-009, SWE-REQ-036) ---------- */

static uint8_t g_motor_status = MOTOR_STATUS_OK;

/* ---------- Private helpers ---------- */

/**
 * @brief Set PWM duty cycle for motor enable.
 * @param duty  Duty cycle 0..100 (percentage).
 *
 * Traces: SWE-REQ-007
 */
static void SetPwmDuty(uint8_t duty)
{
    uint32_t period;
    uint32_t pulse;

    period = __HAL_TIM_GET_AUTORELOAD(&htim2);
    pulse  = ((uint32_t)duty * (period + 1U)) / 100U;
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pulse);
}

/* ---------- Public API ---------- */

void MotorDriver_Init(void)
{
    /* Ensure motor is OFF (SWE-REQ-020) */
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);

    /* Start PWM with 0% duty */
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    SetPwmDuty(0U);

    g_motor_status = MOTOR_STATUS_OK;
}

void MotorDriver_Drive(uint8_t direction, uint8_t enable)
{
    if (enable == MOTOR_DISABLE)
    {
        MotorDriver_Stop();
        return;
    }

    /* SWE-REQ-007: set direction pins via L298N IN1/IN2 */
    if (direction == MOTOR_DIR_FORWARD)
    {
        HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
    }
    else /* MOTOR_DIR_REVERSE */
    {
        HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_SET);
    }

    /* SWE-REQ-007: enable motor with default duty (SWE-REQ-035: configurable) */
    SetPwmDuty(MOTOR_DEFAULT_DUTY);
    g_motor_status = MOTOR_STATUS_OK;
}

void MotorDriver_Stop(void)
{
    /* SWE-REQ-008, SWE-REQ-025: immediate stop – all outputs off */
    SetPwmDuty(0U);
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
}

uint8_t MotorDriver_GetStatus(void)
{
    return g_motor_status;
}
