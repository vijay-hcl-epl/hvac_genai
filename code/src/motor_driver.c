/**
 * @file motor_driver.c
 * @brief Motor Driver implementation – L298N control via STM32 GPIO/PWM.
 *
 * Software Unit : Motor Driver
 * Traces        : SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025,
 *                 SWE-REQ-036, SWE-REQ-038
 * Platform      : STM32F407G-DISC1, L298N H-Bridge, Timer-based PWM
 */

#include "motor_driver.h"
#include "stm32f4xx_hal.h"

/* ---------- Platform GPIO / Timer mapping (env-setup) ------------------ */
/*
 * L298N connections on STM32F407G-DISC1:
 *   IN1 – PB0  (direction A)    GPIO output
 *   IN2 – PB1  (direction B)    GPIO output
 *   ENA – PA0  (PWM enable)     TIM2 Channel 1
 */
#define MOTOR_IN1_PORT   GPIOB
#define MOTOR_IN1_PIN    GPIO_PIN_0
#define MOTOR_IN2_PORT   GPIOB
#define MOTOR_IN2_PIN    GPIO_PIN_1

extern TIM_HandleTypeDef htim2;  /* TIM2 – PWM for motor enable */
#define MOTOR_PWM_CHANNEL  TIM_CHANNEL_1

/* ---------- Static data (SWE-REQ-036, SWE-REQ-038) --------------------- */
static MotorDriverData_t motorData;

/* ---------- Private helpers -------------------------------------------- */

/**
 * @brief Set direction GPIO pins for L298N.
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

        case MOTOR_DIR_STOP: /* fall-through */
        default:
            HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
            break;
    }
}

/* ---------- Public API ------------------------------------------------- */

void MotorDriver_Init(void)
{
    motorData.direction = MOTOR_DIR_STOP;
    motorData.enable    = 0U;
    motorData.pwmDuty   = 0U;
    motorData.status    = MOTOR_STATUS_IDLE;

    /* Ensure motor is OFF at init (SWE-REQ-020) */
    SetDirectionPins(MOTOR_DIR_STOP);
    __HAL_TIM_SET_COMPARE(&htim2, MOTOR_PWM_CHANNEL, 0U);
    HAL_TIM_PWM_Start(&htim2, MOTOR_PWM_CHANNEL);
}

void MotorDriver_Drive(MotorDirection_t dir, uint8_t enable)
{
    if ((dir == MOTOR_DIR_FORWARD) || (dir == MOTOR_DIR_REVERSE))
    {
        motorData.direction = dir;
        motorData.enable    = enable;

        SetDirectionPins(dir);

        if (enable != 0U)
        {
            motorData.pwmDuty = MOTOR_DEFAULT_PWM_DUTY;
            __HAL_TIM_SET_COMPARE(&htim2, MOTOR_PWM_CHANNEL,
                                  (uint32_t)motorData.pwmDuty);
            motorData.status = MOTOR_STATUS_RUNNING;
        }
        else
        {
            __HAL_TIM_SET_COMPARE(&htim2, MOTOR_PWM_CHANNEL, 0U);
            motorData.status = MOTOR_STATUS_IDLE;
        }
    }
    else
    {
        /* Invalid direction – stop (SWE-REQ-008) */
        MotorDriver_Stop();
    }
}

void MotorDriver_Stop(void)
{
    motorData.direction = MOTOR_DIR_STOP;
    motorData.enable    = 0U;
    motorData.pwmDuty   = 0U;
    motorData.status    = MOTOR_STATUS_IDLE;

    SetDirectionPins(MOTOR_DIR_STOP);
    __HAL_TIM_SET_COMPARE(&htim2, MOTOR_PWM_CHANNEL, 0U);
}

MotorStatus_t MotorDriver_GetStatus(void)
{
    return motorData.status;
}
