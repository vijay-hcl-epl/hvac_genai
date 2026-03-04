#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>
void GPIO_Init(void);
void GPIO_Set(uint8_t pin);
void GPIO_Clear(uint8_t pin);
#endif
