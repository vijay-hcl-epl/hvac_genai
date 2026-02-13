#include "uart_cmd_handler.h"
#include "stm32f4xx_hal.h"

static int8_t last_cmd = -1;

void uart_cmd_init(void)
{
    /* MISRA: Rule 8.7 – Variable last_cmd only used in this module, declared static */
    // Initialize UART hardware using Cube/HAL configuration
    // Assume MX_USART2_UART_Init() etc. have been called
    last_cmd = -1;
}

int8_t uart_cmd_get(void)
{
    uint8_t rx = 0U;
    /* MISRA: Rule 9.1 – Variable rx explicitly initialized */
    if (HAL_UART_Receive(&huart2, &rx, 1, 0) == HAL_OK) {
        if ((rx >= '0') && (rx <= '5')) {
            last_cmd = (int8_t)(rx - '0');
            return last_cmd;
        }
    }
    return -1;
}
