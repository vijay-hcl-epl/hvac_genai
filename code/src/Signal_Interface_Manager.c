#include "Signal_Interface_Manager.h"
#include "Application_Layer.h"

static sim_uart_input_t sim_uart;
static sim_adc_reg_t sim_adc;
static sim_state_t sim_state = SIM_WAIT_UART;

void SIM_Init(void) {
    sim_uart.uart_len = 0;
    sim_adc.adc_value = 0;
    sim_state = SIM_WAIT_UART;
}

void SIM_Task(void) {
    switch(sim_state) {
        case SIM_WAIT_UART:
            // Poll UART input (stub for integration)
            // ...
            sim_state = SIM_DECODE_CMD;
            break;
        case SIM_DECODE_CMD:
            // Check/Decode UART buffer (stub)
            // ...
            sim_state = SIM_WAIT_ADC;
            break;
        case SIM_WAIT_ADC:
            // Wait for valid ADC value (stub)
            // ...
            sim_state = SIM_TRANSLATE_POS;
            break;
        case SIM_TRANSLATE_POS:
            // Invoke Application Layer with ADC
            APP_ReceivePosition(sim_adc.adc_value);
            sim_state = SIM_WAIT_UART;
            break;
    }
}
