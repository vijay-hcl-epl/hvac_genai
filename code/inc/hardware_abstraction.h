#ifndef HARDWARE_ABSTRACTION_H
#define HARDWARE_ABSTRACTION_H

#include <stdint.h>
#include <stdbool.h>

// Init peripherals (GPIO, ADC, PWM, UART)
int Init_Hardware(void);
int GPIO_Write(uint8_t pin, bool val);
int PWM_Set(uint8_t channel, uint16_t value);
uint16_t ADC_Read(uint8_t channel);

#endif // HARDWARE_ABSTRACTION_H
