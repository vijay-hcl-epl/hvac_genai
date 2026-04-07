#include "position_feedback.h"
#include <stm32f4xx.h>
#define NUM_POSITIONS 6
static const uint16_t CalibTable[NUM_POSITIONS] = {100, 500, 1000, 1500, 2000, 2500};
static const uint16_t LOW = 100;
static const uint16_t HIGH = 2500;
void position_feedback_get(uint8_t *pos, Status_t *status) {
    uint16_t adc = 0; // TODO: Implement ADC_read for STM32F4
    // Map ADC to logical position
    *pos = 0xFF;
    *status = STATUS_ERROR;
    for (uint8_t i = 0; i < NUM_POSITIONS; ++i) {
        if (adc == CalibTable[i]) {
            *pos = i;
            *status = STATUS_OK;
            return;
        }
    }
    if (adc < LOW || adc > HIGH) {
        *status = STATUS_ERROR;
        return;
    }
}
void position_feedback_init(void) {
    // No-op for now
}
