#ifndef SIGNAL_INTERFACE_MANAGER_H
#define SIGNAL_INTERFACE_MANAGER_H

#include <stdint.h>

// UART Input Buffer
typedef struct {
    uint8_t uart_buf[16];
    uint8_t uart_len;
} sim_uart_input_t;

// ADC Value Registry
typedef struct {
    uint16_t adc_value;
} sim_adc_reg_t;

// State Machine Enum
typedef enum {
    SIM_WAIT_UART = 0,
    SIM_DECODE_CMD,
    SIM_WAIT_ADC,
    SIM_TRANSLATE_POS
} sim_state_t;

// Function Declarations
void SIM_Init(void);
void SIM_Task(void);

#endif // SIGNAL_INTERFACE_MANAGER_H
