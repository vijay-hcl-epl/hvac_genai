#ifndef UART_LIN_DRIVER_H
#define UART_LIN_DRIVER_H
#include <stdint.h>

#define UART_LIN_OK     0
#define UART_LIN_ERROR  1

typedef enum { UART_MODE, LIN_MODE } SerialMode;

typedef struct {
    SerialMode mode;
    uint32_t baudrate;
} SerialConfig;

void Serial_init(const SerialConfig* config);
uint8_t Serial_tx(const uint8_t* data, uint16_t len);
uint8_t Serial_rx(uint8_t* data, uint16_t maxlen);
uint8_t Serial_status(void);

#endif // UART_LIN_DRIVER_H
