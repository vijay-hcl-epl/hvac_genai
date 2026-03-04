#ifndef SYSTEM_CONFIG_DATA_H
#define SYSTEM_CONFIG_DATA_H
#include <stdint.h>
#include <stdbool.h>

typedef enum { SYS_STATE_INIT = 0, SYS_STATE_READY, SYS_STATE_ERROR } system_state_t;

// ADC ranges for each position
extern const uint16_t adc_ranges[6];

// Global state
uint8_t get_system_power_status(void);

// Other: add getters/setters as needed for shared configuration/state

#endif // SYSTEM_CONFIG_DATA_H
