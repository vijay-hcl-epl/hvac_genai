/**
 * @file motor_driver.c
 * @brief Motor Driver implementation – GPIO direction + PWM enable for L298N.
 *
 * Traces: SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025, SWE-REQ-036, SWE-REQ-038
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, bare-metal
 *
 * Pin mapping (env-setup: L298N H-Bridge):
 *   IN1 (direction A) : PB0  – GPIO output
 *   IN2 (direction B) : PB1  – GPIO output
 *   ENA (PWM enable)  : PA0  – TIM2_CH1 PWM output
 */

#include "motor_driver.h"
#include "stm32f4xx_hal.h"

/* ---- Hardware pin definitions (env-setup) ---- */

#define MOTOR_IN1_PORT      GPIOB
#define MOTOR_IN1_PIN       GPIO_PIN_0

#define MOTOR_IN2_PORT      GPIOB
#define MOTOR_IN2_PIN       GPIO_PIN_1

/** Timer handle for PWM – assumed configured by SystemInit (CubeMX) */
extern TIM_HandleTypeDef htim2;

/** PWM channel used for motor enable */
#define MOTOR_PWM_CHANNEL   TIM_CHANNEL_1

/** Default PWM duty for motor running (percentage of ARR).
 *  Configurable responsiveness parameter (SWE-REQ-035). */
#define MOTOR_PWM_DUTY_RUN  (800U)   /* 80 % of 1000 ARR */

#define MOTOR_PWM_DUTY_STOP (0U)

/* ---- Internal static state (SWE-REQ-009, SWE-REQ-036) ---- */

static MotorStatus_t g_motor_status;

/* ================================================================== */

void MotorDriver_Init(void)
{
    /* Set direction pins LOW, stop PWM → motor OFF (SWE-REQ-008, SWE-REQ-020) */
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);

    __HAL_TIM_SET_COMPARE(&htim2, MOTOR_PWM_CHANNEL, MOTOR_PWM_DUTY_STOP);
    HAL_TIM_PWM_Start(&htim2, MOTOR_PWM_CHANNEL);

    g_motor_status = MOTOR_STATUS_STOPPED;
}

/* ------------------------------------------------------------------ */

void MotorDriver_Drive(MotorDirection_t direction, uint8_t enable)
{
    if (enable == 0U)
    {
        MotorDriver_Stop();
        return;
    }

    switch (direction)
    {
        case MOTOR_DIR_FORWARD:
            /* IN1=HIGH, IN2=LOW → forward rotation (SWE-REQ-007) */
            HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
            __HAL_TIM_SET_COMPARE(&htim2, MOTOR_PWM_CHANNEL, MOTOR_PWM_DUTY_RUN);
            g_motor_status = MOTOR_STATUS_RUNNING;
            break;

        case MOTOR_DIR_REVERSE:
            /* IN1=LOW, IN2=HIGH → reverse rotation (SWE-REQ-007) */
            HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_SET);
            __HAL_TIM_SET_COMPARE(&htim2, MOTOR_PWM_CHANNEL, MOTOR_PWM_DUTY_RUN);
            g_motor_status = MOTOR_STATUS_RUNNING;
            break;

        case MOTOR_DIR_STOP:
        default:
            MotorDriver_Stop();
            break;
    }
}

/* ------------------------------------------------------------------ */

void MotorDriver_Stop(void)
{
    /* All outputs OFF → safe state (SWE-REQ-008, SWE-REQ-025) */
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(&htim2, MOTOR_PWM_CHANNEL, MOTOR_PWM_DUTY_STOP);
    g_motor_status = MOTOR_STATUS_STOPPED;
}

/* ------------------------------------------------------------------ */

MotorStatus_t MotorDriver_GetStatus(void)
{
    return g_motor_status;
}
