#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

#define CMD_BUF_SIZE 8

typedef enum {
    UART_OK = 0,
    UART_NO_CMD = 1,
    UART_ERR_RANGE = 2
} UART_Status_t;

void InputHandler_Init(void);
void InputHandler_UART_RxHandler(uint8_t rx_byte);
bool InputHandler_CommandPending(void);
int8_t InputHandler_GetPendingCommand(void);
void InputHandler_ClearPending(void);
UART_Status_t InputHandler_GetStatus(void);

#endif // INPUT_HANDLER_H
