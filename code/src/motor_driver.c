/**
 * @file motor_driver.c
 * @brief Motor Driver Software Unit – Implementation
 *
 * Traceability:
 *   SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025,
 *   SWE-REQ-036, SWE-REQ-038
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal, L298N H-Bridge
 *
 * Pin Assignment (assumed, configurable via defines below):
 *   Motor IN1 (direction A) : PB0  (GPIO output)
 *   Motor IN2 (direction B) : PB1  (GPIO output)
 *   Motor ENA (PWM enable)  : PA0  (TIM2_CH1 PWM)
 *
 * L298N truth table:
 *   IN1=H, IN2=L  → Forward
 *   IN1=L, IN2=H  → Reverse
 *   IN1=L, IN2=L  → Stop (coast)
 *   ENA = PWM duty → Speed control
 *
 * [SWE-REQ-007, SWE-REQ-016, SWE-REQ-038]
 */

#include "motor_driver.h"
#include "stm32f4xx_hal.h"

/* ---------- Hardware binding (env-setup: GPIO + PWM) ---------- */

/**
 * @brief Timer handle for PWM – TIM2 Channel 1 on PA0.
 *        Declared extern; created by peripheral-init in system_init.
 *        [SWE-REQ-016, SWE-REQ-019]
 */
extern TIM_HandleTypeDef htim2;

/** Motor direction GPIO – IN1 */
#define MOTOR_IN1_PORT   GPIOB
#define MOTOR_IN1_PIN    GPIO_PIN_0

/** Motor direction GPIO – IN2 */
#define MOTOR_IN2_PORT   GPIOB
#define MOTOR_IN2_PIN    GPIO_PIN_1

/** PWM Timer channel for ENA */
#define MOTOR_PWM_CHANNEL  TIM_CHANNEL_1

/* ---------- Static module data ---------- */
/* [SWE-REQ-009, SWE-REQ-036, SWE-REQ-038] */

/** Current motor direction */
static MotorDirection_t s_direction = MOTOR_DIR_STOP;

/** Current motor enable state */
static bool s_enabled = false;

/** Current motor status */
static MotorStatus_t s_status = MOTOR_STATUS_STOPPED;

/** PWM duty cycle value (auto-reload compare value).
 *  Computed once at init from MOTOR_DEFAULT_DUTY_PERCENT.
 *  [SWE-REQ-035, SWE-REQ-038] */
static uint32_t s_pwmCompare = 0U;

/* ---------- Private helpers ---------- */

/**
 * @brief Set direction GPIO pins per L298N truth table.
 *        [SWE-REQ-007]
 */
static void SetDirectionPins(MotorDirection_t dir)
{
    switch (dir)
    {
        case MOTOR_DIR_FORWARD:
            HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
            break;

        case MOTOR_DIR_REVERSE:
            HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_SET);
            break;

        case MOTOR_DIR_STOP:
        default:
            HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
            break;
    }
}

/* ---------- Public API ---------- */

/**
 * @brief Initialise the Motor Driver unit – all outputs safe (OFF).
 *        [SWE-REQ-020, SWE-REQ-008]
 */
void MotorDriver_Init(void)
{
    s_direction = MOTOR_DIR_STOP;
    s_enabled   = false;
    s_status    = MOTOR_STATUS_STOPPED;

    /* Compute PWM compare value for default duty
     * [SWE-REQ-035] */
    uint32_t period = __HAL_TIM_GET_AUTORELOAD(&htim2);
    s_pwmCompare = (period * MOTOR_DEFAULT_DUTY_PERCENT) / 100U;

    /* Ensure motor is OFF at init [SWE-REQ-008] */
    SetDirectionPins(MOTOR_DIR_STOP);
    __HAL_TIM_SET_COMPARE(&htim2, MOTOR_PWM_CHANNEL, 0U);
    HAL_TIM_PWM_Start(&htim2, MOTOR_PWM_CHANNEL);
}

/**
 * @brief Drive the motor in the specified direction.
 *        [SWE-REQ-007, SWE-REQ-016]
 */
void MotorDriver_Drive(MotorDirection_t dir, bool enable)
{
    s_direction = dir;
    s_enabled   = enable;

    if (enable == true)
    {
        SetDirectionPins(dir);
        __HAL_TIM_SET_COMPARE(&htim2, MOTOR_PWM_CHANNEL, s_pwmCompare);
        s_status = MOTOR_STATUS_RUNNING;
    }
    else
    {
        SetDirectionPins(MOTOR_DIR_STOP);
        __HAL_TIM_SET_COMPARE(&htim2, MOTOR_PWM_CHANNEL, 0U);
        s_status = MOTOR_STATUS_STOPPED;
    }
}

/**
 * @brief Immediately stop the motor (all outputs OFF, safe state).
 *        [SWE-REQ-008, SWE-REQ-025, SWE-REQ-032]
 */
void MotorDriver_Stop(void)
{
    SetDirectionPins(MOTOR_DIR_STOP);
    __HAL_TIM_SET_COMPARE(&htim2, MOTOR_PWM_CHANNEL, 0U);
    s_direction = MOTOR_DIR_STOP;
    s_enabled   = false;
    s_status    = MOTOR_STATUS_STOPPED;
}

/**
 * @brief Retrieve current motor status.
 *        [SWE-REQ-040]
 */
MotorStatus_t MotorDriver_GetStatus(void)
{
    return s_status;
}
