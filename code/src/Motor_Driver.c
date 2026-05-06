#include "Motor_Driver.h"
#include "stm32f4xx_hal.h"

// Set GPIO and PWM assignments as per CubeMX output and shield wiring.
#define MOTOR_DIR_GPIO_Port GPIOB
#define MOTOR_DIR_Pin GPIO_PIN_0
#define MOTOR_EN_GPIO_Port GPIOB
#define MOTOR_EN_Pin GPIO_PIN_1
#define MOTOR_PWM_TIM htim3
#define MOTOR_PWM_CHANNEL TIM_CHANNEL_1

extern TIM_HandleTypeDef MOTOR_PWM_TIM;

static bool motor_active = false;
static MotorDirection_t last_direction;

void MotorDriver_Init(void)
{
    motor_active = false;
    last_direction = MOTOR_DIR_FORWARD;
    // Stop PWM, clear pins
    HAL_GPIO_WritePin(MOTOR_EN_GPIO_Port, MOTOR_EN_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, GPIO_PIN_RESET);
    HAL_TIM_PWM_Stop(&MOTOR_PWM_TIM, MOTOR_PWM_CHANNEL);
}

void MotorDriver_Drive(MotorDirection_t direction, bool enable)
{
    if (enable) {
        HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, (direction == MOTOR_DIR_FORWARD ? GPIO_PIN_RESET : GPIO_PIN_SET));
        HAL_GPIO_WritePin(MOTOR_EN_GPIO_Port, MOTOR_EN_Pin, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&MOTOR_PWM_TIM, MOTOR_PWM_CHANNEL, 800); // Set duty cycle (adjust as needed)
        HAL_TIM_PWM_Start(&MOTOR_PWM_TIM, MOTOR_PWM_CHANNEL);
        last_direction = direction;
        motor_active = true;
    } else {
        MotorDriver_Stop();
    }
}

void MotorDriver_Stop(void)
{
    HAL_GPIO_WritePin(MOTOR_EN_GPIO_Port, MOTOR_EN_Pin, GPIO_PIN_RESET);
    HAL_TIM_PWM_Stop(&MOTOR_PWM_TIM, MOTOR_PWM_CHANNEL);
    motor_active = false;
}

bool MotorDriver_IsActive(void)
{
    return motor_active;
}
