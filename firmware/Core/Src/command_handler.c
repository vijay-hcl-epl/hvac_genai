#include "command_handler.h"
#include "stm32f4xx_hal.h"

uint8_t CommandHandler_PollCommand(uint8_t *cmd_out)
{
    uint8_t rx = 0U;
    uint8_t ret = 0U;
    HAL_StatusTypeDef status;

    /* Extern declaration moved to block scope as per MISRA 8.9 */
    extern UART_HandleTypeDef huart2;

    status = HAL_UART_Receive(&huart2, &rx, 1U, 10U);
    if (status == HAL_OK)
    {
        if ((rx >= (uint8_t)'0') && (rx <= (uint8_t)'5'))
        {
            /* MISRA 10.1/10.8: Cast operands before subtraction */
            *cmd_out = (uint8_t)((uint8_t)rx - (uint8_t)'0');
            ret = 1U;
        }
    }
    return ret;
}