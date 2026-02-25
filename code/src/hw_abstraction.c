#include "hw_abstraction.h"
#include "stm32f4xx_hal.h"

void HW_UART_Init(void) {}
void HW_UART_Transmit(uint8_t* data, uint16_t size) {}
void HW_UART_Receive_IT(uint8_t* data, uint16_t size) {}

void HW_ADC_Init(void) {}
uint16_t HW_ADC_Read(void) { return 0; /* Replace with actual ADC code */ }

void HW_GPIO_Init(void) {}
void HW_GPIO_Set(uint16_t pin, bool value) {}

void HW_PWM_Init(void) {}
void HW_PWM_Set(uint16_t channel, uint8_t duty_cycle) {}
void HW_PWM_Enable(uint16_t channel, bool enable) {}