/**
 * @file motor_driver.c
 * @brief Motor Driver implementation – L298N control via STM32 HAL GPIO/PWM.
 *
 * Traces: SWE-REQ-007, SWE-REQ-008, SWE-REQ-016, SWE-REQ-025,
 *         SWE-REQ-036, SWE-REQ-038
 *
 * Platform: STM32F407G-DISC1, STM32 HAL, L298N H-Bridge, bare-metal
 *
 * Pin mapping (assumed):
 *   IN1 (direction A) : PB0  – GPIO output
 *   IN2 (direction B) : PB1  – GPIO output
 *   ENA (PWM enable)  : PA0  – TIM2 CH1 PWM output
 */

#include "motor_driver.h"
#include "stm32f4xx_hal.h"

/* ---- Pin definitions -------------------------------------------------- */

#define MOTOR_IN1_PORT   GPIOB
#define MOTOR_IN1_PIN    GPIO_PIN_0
#define MOTOR_IN2_PORT   GPIOB
#define MOTOR_IN2_PIN    GPIO_PIN_1

/* ---- Extern HAL handle (defined in system_init.c) --------------------- */
extern TIM_HandleTypeDef htim2;

/* ---- Private data ----------------------------------------------------- */

static MotorStatus_t s_motor_status;

/** Static PWM duty value (SWE-REQ-038, SWE-REQ-035). */
static uint8_t s_pwm_duty = MOTOR_DEFAULT_DUTY;

/* ---- Private helpers -------------------------------------------------- */

/**
 * @brief Set PWM compare value proportional to duty%.
 */
static void Motor_SetPWM(uint8_t duty_percent)
{
    uint32_t period  = __HAL_TIM_GET_AUTORELOAD(&htim2);
    uint32_t compare = (period * (uint32_t)duty_percent) / 100U;
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, compare);
}

/* ---- Public API ------------------------------------------------------- */

void MotorDriver_Init(void)
{
    /* Ensure outputs are LOW (motor OFF – SWE-REQ-020). */
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);

    /* Start PWM with 0% duty. */
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    Motor_SetPWM(0U);

    s_motor_status = MOTOR_STATUS_IDLE;
}

void MotorDriver_Drive(MotorDir_t dir, bool enable)
{
    if (!enable)
    {
        MotorDriver_Stop();
        return;
    }

    switch (dir)
    {
        case MOTOR_DIR_FORWARD:
            HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
            Motor_SetPWM(s_pwm_duty);
            s_motor_status = MOTOR_STATUS_RUNNING;
            break;

        case MOTOR_DIR_REVERSE:
            HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_SET);
            Motor_SetPWM(s_pwm_duty);
            s_motor_status = MOTOR_STATUS_RUNNING;
            break;

        case MOTOR_DIR_STOP:
        default:
            MotorDriver_Stop();
            break;
    }
}

void MotorDriver_Stop(void)
{
    /* All direction pins LOW, PWM to 0 (SWE-REQ-008, SWE-REQ-025). */
    HAL_GPIO_WritePin(MOTOR_IN1_PORT, MOTOR_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IN2_PORT, MOTOR_IN2_PIN, GPIO_PIN_RESET);
    Motor_SetPWM(0U);
    s_motor_status = MOTOR_STATUS_IDLE;
}

MotorStatus_t MotorDriver_GetStatus(void)
{
    return s_motor_status;
}
