#include "system_startup.h"
#include "command_parser.h"
#include "flap_control_logic.h"
#include "feedback_processor.h"
#include "main.h"

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_ADC1_Init();
    MX_TIMx_Init();

    system_init();

    while (1) {
        // Poll UART for RX (blocking or via callback registration)
        uint8_t rx_byte;
        if (HAL_UART_Receive(&huart2, &rx_byte, 1, 10) == HAL_OK) {
            command_parser_on_uart_rx(rx_byte);
        }
        // Command forwarding to control
        command_t cmd = command_parser_get_latest();
        flap_control_new_command(cmd.latest_cmd, cmd.valid);

        // Feedback processing
        feedback_processor_update();
        bool valid;
        uint8_t pos = feedback_processor_get_position(&valid);
        flap_control_feedback_update(pos, valid);

        flap_control_task();
    }
}
