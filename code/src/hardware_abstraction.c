#include "hardware_abstraction.h"

int Init_Hardware(void) {
    // TODO: configure all peripherals (GPIO, ADC, UART, PWM)
    return 0;
}

int GPIO_Write(uint8_t pin, bool val) {
    // TODO: implement MCU-specific write
    (void)pin; (void)val;
    return 0;
}

int PWM_Set(uint8_t channel, uint16_t value) {
    // TODO: implement
    (void)channel; (void)value;
    return 0;
}

uint16_t ADC_Read(uint8_t channel) {
    // TODO: return dummy for simulation
    (void)channel;
    return 1000; // Simulation value
}
