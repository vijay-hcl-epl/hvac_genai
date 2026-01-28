/**
 @file command_handler.c
 @brief Implementation of UART command parser/validation (SWE-REQ-001..004)
 @responsibility: Receives and validates UART-based flap position commands. */
#include "command_handler.h"
#define CMD_MIN_POS (0U)
#define CMD_MAX_POS (5U)

static uint8_t target_position = CMD_MIN_POS;

void CommandHandler_Init(void)
{
    target_position = CMD_MIN_POS;
}

bool CommandHandler_ProcessByte(uint8_t uart_byte, uint8_t *out_position)
{
    if ((uart_byte >= CMD_MIN_POS) && (uart_byte <= CMD_MAX_POS))
    {
        target_position = uart_byte;
        if (out_position != (void *)0)
        {
            *out_position = target_position;
        }
        return true;
    }
    return false;
}

uint8_t CommandHandler_GetTargetPosition(void)
{
    return target_position;
}
