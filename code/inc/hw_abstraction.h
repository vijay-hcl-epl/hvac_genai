#ifndef HW_ABSTRACTION_H
#define HW_ABSTRACTION_H

#include <stdint.h>
#include <stdbool.h>

// UART HW Abstraction
void HW_UART_Init(void);
void HW_UART_Transmit(uint8_t* data, uint16_t size);
void HW_UART_Receive_IT(uint8_t* data, uint16_t size);

// ADC HW Abstraction
void HW_ADC_Init(void);
uint16_t HW_ADC_Read(void);

// GPIO HW Abstraction
void HW_GPIO_Init(void);
void HW_GPIO_Set(uint16_t pin, bool value);

// PWM HW Abstraction
void HW_PWM_Init(void);
void HW_PWM_Set(uint16_t channel, uint8_t duty_cycle);
void HW_PWM_Enable(uint16_t channel, bool enable);

#endif // HW_ABSTRACTION_H
