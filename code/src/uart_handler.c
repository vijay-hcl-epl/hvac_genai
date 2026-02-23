#include "uart_handler.h"
#include "stm32f4xx_hal.h"
#include <string.h>

static uint8_t rx_char = 0;
static volatile int uart_cmd = -1;
extern UART_HandleTypeDef huart2;

void UART_Init(void) {
    // UART configured elsewhere using HAL
    HAL_UART_Receive_IT(&huart2, &rx_char, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART2) {
        if (rx_char >= '0' && rx_char <= '5') {
            uart_cmd = rx_char - '0';
        } else {
            uart_cmd = -1;
        }
        HAL_UART_Receive_IT(&huart2, &rx_char, 1);
    }
}

int UART_GetCommand(void) {
    int value = uart_cmd;
    uart_cmd = -1;
    return value;
}
