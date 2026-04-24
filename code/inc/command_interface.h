#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H
#include <stdint.h>
#include <stdbool.h>

// Called to process UART RX event, parse, validate, and send to control.
void CI_ProcessUartInput(const char *rx_buf, uint8_t len);

// For use by main to initialize the interface.
void CI_Init(void);

#endif // COMMAND_INTERFACE_H
