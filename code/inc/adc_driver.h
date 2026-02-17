#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H
#include <stdint.h>

typedef struct {
    uint8_t resolution; // bits
    uint8_t channel;
} ADC_Config;

void ADC_init(const ADC_Config* config);
uint8_t ADC_start(uint8_t channel);
uint16_t ADC_result(void);
uint8_t ADC_status(void);

#endif // ADC_DRIVER_H
