// RAG_SOURCE: infineon-tle985xqx-usermanual-en.pdf §4 (nonvolatile storage)
#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H
#include <stdint.h>
typedef struct {
    uint16_t thresholds[6]; // ADC calibration values for 0-5
    uint32_t uart_baud;
    uint16_t pin_map;
} ConfigData;
void ConfigData_Load(void);
ConfigData* ConfigData_Get(void);
#endif
