/**
 * @file motor_driver.c
 * @brief Motor Driver implementation for L298N via STM32 HAL GPIO + PWM.
 *
 * Software Unit: Motor Driver
 * Traces: SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025, SWE-REQ-036, SWE-REQ-038
 *
 * Platform: STM32F407G-DISC1 / STM32 HAL / L298N Dual H-Bridge
 * No dynamic allocation (SWE-REQ-036).  All state is static.
 *
 * ASSUMPTIONS / WIRING NOTE (not verified on hardware):
 *   - L298N IN1 → PB0  (GPIO output, motor direction A)
 *   - L298N IN2 → PB1  (GPIO output, motor direction B)
 *   - L298N ENA → PA0  (TIM2 CH1 PWM output, motor enable / speed)
 *   - PWM period and duty cycle values are design placeholders.
 *     Calibrate PWM frequency and duty for the 12 V DC geared motor.
 *   - htim2 is declared extern; it is initialised in system_init.c.
 */

#include "motor_driver.h"
#include "stm32f4xx_hal.h"

/* ---- Extern HAL timer handle (initialised in system_init.c) ---- */
extern TIM_HandleTypeDef htim2;

/* ---- Pin definitions (placeholder – match to actual wiring) ---- */

#define MOTOR_IN1_PORT   GPIOB
#define MOTOR_IN1_PIN    GPIO_PIN_0

#define MOTOR_IN2_PORT   GPIOB
#define MOTOR_IN2_PIN    GPIO_PIN_1

/* PWM channel for ENA on TIM2_CH1 */
#define MOTOR_PWM_CHANNEL  TIM_CHANNEL_1

/**
 * Configurable PWM duty cycle (0..htim2.Init.Period).
 * Design assumption: 70 % duty at Period=999 → CCR = 699.
 * SWE-REQ-035: document configurable responsiveness parameter.
 */
#define MOTOR_PWM_DUTY_DEFAULT  699U

/* ---- Module static state [SWE-REQ-009, SWE-REQ-036, SWE-REQ-038] ---- */

static motor_status_t s_status = MOTOR_STATUS_STOPPED;

/* ---- Public API ---- */

void motor_driver_init(void)
{
    /* Direction pins LOW (coast stop) */
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);

    /* Ensure PWM output is stopped */
    HAL_TIM_PWM_Stop(&htim2, MOTOR_PWM_CHANNEL);

    s_status = MOTOR_STATUS_STOPPED;
}

/*
 * SWE-REQ-007 : set GPIO + PWM for direction/enable
 * SWE-REQ-016 : control motor via GPIO/PWM exclusively
 */
void motor_driver_drive(motor_dir_t dir, uint8_t enable)
{
    if (enable == 0U)
    {
        motor_driver_stop();
        return;
    }

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
            motor_driver_stop();
            return;
    }

    /* Set duty cycle and start PWM */
    __HAL_TIM_SET_COMPARE(&htim2, MOTOR_PWM_CHANNEL, MOTOR_PWM_DUTY_DEFAULT);
    HAL_TIM_PWM_Start(&htim2, MOTOR_PWM_CHANNEL);

    s_status = MOTOR_STATUS_RUNNING;
}

/* SWE-REQ-008, SWE-REQ-025, SWE-REQ-032 : immediate safe stop */
void motor_driver_stop(void)
{
    HAL_TIM_PWM_Stop(&htim2, MOTOR_PWM_CHANNEL);
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);

    s_status = MOTOR_STATUS_STOPPED;
}

motor_status_t motor_driver_get_status(void)
{
    return s_status;
}
