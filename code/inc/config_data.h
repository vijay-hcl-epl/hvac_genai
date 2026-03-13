#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H

#include <stdint.h>

typedef struct {
    uint16_t adc_thresholds[6]; // 6 flap positions
    uint32_t baudrate;
    uint8_t uart_channel;
} ConfigData_t;

const ConfigData_t* ConfigData_Get(void);

#endif // CONFIG_DATA_H
