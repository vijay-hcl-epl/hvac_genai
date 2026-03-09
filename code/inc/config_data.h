#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H
#include <stdint.h>

typedef struct {
    uint16_t adc_thresholds[6];
    uint32_t uart_baud;
} ConfigData;

void ConfigData_Init(void);
const ConfigData* ConfigData_Get(void);

#endif // CONFIG_DATA_H
