/**
 * @file motor_driver.c
 * @brief Motor Driver implementation – L298N control via STM32 HAL GPIO/PWM.
 *
 * Traces: SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025, SWE-REQ-036, SWE-REQ-038
 * Platform: STM32F407G-DISC1 / STM32 HAL / L298N
 *
 * Pin mapping (assumed, configurable):
 *   Motor IN1 (direction A) : PB0  (GPIO)
 *   Motor IN2 (direction B) : PB1  (GPIO)
 *   Motor ENA (PWM enable)  : PA0  (TIM2 CH1 PWM)
 */

#include "motor_driver.h"
#include "stm32f4xx_hal.h"

/* ---- Pin / peripheral configuration (static constants) [SWE-REQ-038] ---- */

#define MOTOR_IN1_PORT          GPIOB
#define MOTOR_IN1_PIN           GPIO_PIN_0
#define MOTOR_IN2_PORT          GPIOB
#define MOTOR_IN2_PIN           GPIO_PIN_1

/* PWM Timer handle – expected from STM32CubeMX generated code */
extern TIM_HandleTypeDef htim2;

/** PWM channel for motor enable */
#define MOTOR_PWM_CHANNEL       TIM_CHANNEL_1

/** Timer auto-reload value (set during CubeMX config, assumed 999 for 0–100% mapping) */
#define MOTOR_PWM_PERIOD        (999U)

/* ---- Internal state (static) [SWE-REQ-009, SWE-REQ-036] ---- */
static motor_status_t s_motor_status;
static uint8_t        s_duty_percent;

/* ---- Private helpers ---- */

/**
 * @brief Set PWM duty cycle.
 * @param duty_percent  0–100.
 */
static void set_pwm_duty(uint8_t duty_percent)
{
    uint32_t compare_val;

    if (duty_percent > 100U)
    {
        duty_percent = 100U;
    }
    compare_val = (uint32_t)((uint32_t)MOTOR_PWM_PERIOD * (uint32_t)duty_percent) / 100U;

    __HAL_TIM_SET_COMPARE(&htim2, MOTOR_PWM_CHANNEL, compare_val);
    s_duty_percent = duty_percent;
}

/* ---- Public API ---- */

void motor_driver_init(void)
{
    /* Ensure motor is stopped on init [SWE-REQ-020] */
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);

    /* Start PWM with 0% duty */
    HAL_TIM_PWM_Start(&htim2, MOTOR_PWM_CHANNEL);
    set_pwm_duty(0U);

    s_motor_status = MOTOR_STATUS_STOPPED;
}

void motor_driver_drive(motor_direction_t dir, uint8_t enable)
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
            set_pwm_duty(MOTOR_DEFAULT_DUTY);
            s_motor_status = MOTOR_STATUS_RUNNING;
            break;

        case MOTOR_DIR_REVERSE:
            HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_SET);
            set_pwm_duty(MOTOR_DEFAULT_DUTY);
            s_motor_status = MOTOR_STATUS_RUNNING;
            break;

        case MOTOR_DIR_STOP:
        default:
            motor_driver_stop();
            break;
    }
}

void motor_driver_stop(void)
{
    /* All outputs OFF – safe state [SWE-REQ-008, SWE-REQ-025, SWE-REQ-032] */
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
    set_pwm_duty(0U);
    s_motor_status = MOTOR_STATUS_STOPPED;
}

motor_status_t motor_driver_get_status(void)
{
    return s_motor_status;
}
