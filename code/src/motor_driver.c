/**
 * @file motor_driver.c
 * @brief Motor Driver implementation – L298N H-bridge GPIO/PWM control.
 *
 * Software Unit : Motor Driver
 * Traceability  : SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025,
 *                 SWE-REQ-036, SWE-REQ-038
 *
 * Platform      : STM32F407G-DISC1, STM32 HAL, L298N motor driver
 *
 * CONFIGURATION GAP: GPIO pins for IN1 / IN2 and the timer channel for
 * ENA (PWM) are assumed defaults.  They MUST be validated against the
 * actual wiring between the STM32 board and the L298N module.
 *
 * Assumed wiring (PLACEHOLDER):
 *   IN1 (direction A) : PB0
 *   IN2 (direction B) : PB1
 *   ENA (PWM enable)  : PA0  →  TIM2_CH1  (AF1)
 *
 * Motor direction truth table (L298N):
 *   IN1=H, IN2=L → Forward
 *   IN1=L, IN2=H → Reverse
 *   IN1=L, IN2=L → Stop / coast
 */

#include "motor_driver.h"
#include "stm32f4xx_hal.h"

/* ── Pin definitions (ASSUMED – see gap note) ────────────────────────── */
#define MOTOR_IN1_PORT   GPIOB
#define MOTOR_IN1_PIN    GPIO_PIN_0

#define MOTOR_IN2_PORT   GPIOB
#define MOTOR_IN2_PIN    GPIO_PIN_1

/* ── Timer / PWM handle (configured in system_init.c) ────────────────── */
extern TIM_HandleTypeDef htim2;
#define MOTOR_PWM_CHANNEL   TIM_CHANNEL_1

/* ── Static data (SWE-REQ-036, SWE-REQ-038) ─────────────────────────── */
static MotorDir_t    s_direction = MOTOR_DIR_STOP;
static MotorStatus_t s_status    = MOTOR_STATUS_OK;

/* ── Private helpers ─────────────────────────────────────────────────── */

/**
 * @brief Set PWM duty cycle (0..100 %).
 * @param duty_percent  Duty cycle percentage.
 */
static void SetPwmDuty(uint8_t duty_percent)
{
    uint32_t arr;
    uint32_t ccr;

    if (duty_percent > 100U)
    {
        duty_percent = 100U;
    }

    arr = __HAL_TIM_GET_AUTORELOAD(&htim2);
    ccr = (uint32_t)(((uint32_t)duty_percent * (arr + 1U)) / 100U);
    __HAL_TIM_SET_COMPARE(&htim2, MOTOR_PWM_CHANNEL, ccr);
}

/* ── Public API ──────────────────────────────────────────────────────── */

void MotorDrv_Init(void)
{
    /* Safe state: direction pins LOW, PWM duty 0. */
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);

    HAL_TIM_PWM_Start(&htim2, MOTOR_PWM_CHANNEL);
    SetPwmDuty(0U);

    s_direction = MOTOR_DIR_STOP;
    s_status    = MOTOR_STATUS_OK;
}

void MotorDrv_Drive(MotorDir_t dir, uint8_t enable)
{
    /* SWE-REQ-007: set GPIO and PWM per direction. */
    if (dir == MOTOR_DIR_FORWARD)
    {
        HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
    }
    else if (dir == MOTOR_DIR_REVERSE)
    {
        HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_SET);
    }
    else
    {
        /* STOP */
        HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
    }

    if (enable != 0U)
    {
        SetPwmDuty(MOTOR_DEFAULT_DUTY_PERCENT);
    }
    else
    {
        SetPwmDuty(0U);
    }

    s_direction = dir;
}

void MotorDrv_Stop(void)
{
    /* SWE-REQ-008, SWE-REQ-025: immediate safe stop. */
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
    SetPwmDuty(0U);
    s_direction = MOTOR_DIR_STOP;
}

MotorStatus_t MotorDrv_GetStatus(void)
{
    return s_status;
}
