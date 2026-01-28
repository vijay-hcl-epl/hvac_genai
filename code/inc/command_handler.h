/**
 @file command_handler.h
 @brief UART command parser and validation functionality.
 @responsibility: Receives and validates UART-based flap position commands (SWE-REQ-001..004). */
#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include <stdint.h>
#include <stdbool.h>

/* Initialization */
void CommandHandler_Init(void);

/* Process an incoming UART byte; Returns true and out_position if a valid command is detected. */
bool CommandHandler_ProcessByte(uint8_t uart_byte, uint8_t *out_position);

/* Get the last valid target position set by this handler */
uint8_t CommandHandler_GetTargetPosition(void);

#endif /* COMMAND_HANDLER_H */
