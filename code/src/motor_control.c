#include "motor_control.h"
#include "stm32f4xx_hal.h"

#define MOTOR_PWM_CHANNEL TIM_CHANNEL_1
#define MOTOR_PWM_TIMER   &htim1
#define MOTOR_PIN_EN      GPIO_PIN_6
#define MOTOR_PORT_EN     GPIOB
#define MOTOR_PIN_DIR1    GPIO_PIN_0
#define MOTOR_PORT_DIR1   GPIOA
#define MOTOR_PIN_DIR2    GPIO_PIN_1
#define MOTOR_PORT_DIR2   GPIOA

static motor_state_t motor_state = MOTOR_STOPPED;
static int8_t last_target = -1;

void motor_control_init(void)
{
    motor_state = MOTOR_STOPPED;
    last_target = -1;
    HAL_GPIO_WritePin(MOTOR_PORT_EN, MOTOR_PIN_EN, GPIO_PIN_RESET);
}

motor_status_t motor_move_to(int8_t target_position)
{
    int8_t curr_pos = 0; // replace with actual call if available
    // curr_pos = feedback_get_position();
    if ((target_position < 0) || (target_position >= 6))
        return MOTOR_INVALID_TARGET;
    if (target_position == curr_pos)
        return MOTOR_ALREADY_AT_POSITION;
    // Determine direction (for demo, assume curr_pos < target_position -> forward)
    if (target_position > curr_pos)
    {
        HAL_GPIO_WritePin(MOTOR_PORT_DIR1, MOTOR_PIN_DIR1, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_PORT_DIR2, MOTOR_PIN_DIR2, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(MOTOR_PORT_DIR1, MOTOR_PIN_DIR1, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_PORT_DIR2, MOTOR_PIN_DIR2, GPIO_PIN_SET);
    }
    HAL_GPIO_WritePin(MOTOR_PORT_EN, MOTOR_PIN_EN, GPIO_PIN_SET);
    HAL_TIM_PWM_Start(MOTOR_PWM_TIMER, MOTOR_PWM_CHANNEL);
    motor_state = MOTOR_RUNNING;
    last_target = target_position;
    return MOTOR_OK;
}

void motor_stop(void)
{
    HAL_TIM_PWM_Stop(MOTOR_PWM_TIMER, MOTOR_PWM_CHANNEL);
    HAL_GPIO_WritePin(MOTOR_PORT_EN, MOTOR_PIN_EN, GPIO_PIN_RESET);
    motor_state = MOTOR_STOPPED;
}
