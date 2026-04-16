#include "init_powerup_supervisor.h"
#include "error_input_validator.h"
#include "motor_control_unit.h"
#include "position_sensor_mapper.h"
#include "uart_command_handler.h"
#include "led_status_indicator.h"

int main(void)
{
    init_powerup_supervisor_t init_ctx = {0};
    error_input_validator_t error_ctx = {0};
    motor_control_unit_t motor_ctx = {0};
    position_sensor_mapper_t pos_ctx = {0};
    uart_command_handler_t uart_ctx = {0};
    led_status_indicator_t led_ctx = {0};

    /* Initialization phase */
    init_powerup_supervisor_resp_1(&init_ctx);
    init_powerup_supervisor_resp_2(&init_ctx);
    init_powerup_supervisor_resp_3(&init_ctx);
    init_powerup_supervisor_resp_4(&init_ctx);

    for(;;)
    {
        /* UART handling */
        uart_command_handler_resp_1(&uart_ctx);
        uart_command_handler_resp_2(&uart_ctx);
        uart_command_handler_resp_3(&uart_ctx);

        /* ADC and position processing */
        position_sensor_mapper_resp_1(&pos_ctx);
        position_sensor_mapper_resp_2(&pos_ctx);
        position_sensor_mapper_resp_3(&pos_ctx);
        position_sensor_mapper_resp_4(&pos_ctx);

        /* Validation & safety checks */
        error_input_validator_resp_1(&error_ctx);
        error_input_validator_resp_2(&error_ctx);
        error_input_validator_resp_3(&error_ctx);

        /* Motor control logic */
        motor_control_unit_resp_1(&motor_ctx);
        motor_control_unit_resp_2(&motor_ctx);
        motor_control_unit_resp_3(&motor_ctx);
        motor_control_unit_resp_4(&motor_ctx);

        /* LED updates */
        led_status_indicator_resp_1(&led_ctx);
        led_status_indicator_resp_2(&led_ctx);
        led_status_indicator_resp_3(&led_ctx);
    }
    return 0;
}
