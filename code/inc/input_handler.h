#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

// API: Call on UART Rx event
void input_handler_rx_byte(uint8_t byte);
// API: Init handler
void input_handler_init(void);
// API: Test inject
void input_handler_test_inject(uint8_t *frame, uint8_t len);

#endif // INPUT_HANDLER_H
