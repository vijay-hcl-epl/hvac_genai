#include "uart_lin_driver.h"
// [TBD — Not in source]: HW register access macros, ISR, error status masks
static SerialConfig g_cfg;
void Serial_init(const SerialConfig* config) { g_cfg = *config; /* [TBD — HW init] */ }
uint8_t Serial_tx(const uint8_t* data, uint16_t len) { return UART_LIN_OK; /* [TBD — HW send] */ }
uint8_t Serial_rx(uint8_t* data, uint16_t maxlen) { return UART_LIN_OK; /* [TBD — HW receive] */ }
uint8_t Serial_status(void) { return UART_LIN_OK; /* [TBD — HW status] */ }
