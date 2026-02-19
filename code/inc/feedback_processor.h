#ifndef FEEDBACK_PROCESSOR_H
#define FEEDBACK_PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>
#define FB_MAP_SIZE 8

typedef enum {
    FB_STATE_INIT = 0,
    FB_STATE_READY,
    FB_STATE_INVALID
} fb_state_t;

typedef struct {
    uint16_t adc_sample;
    uint8_t position;
    bool valid;
    fb_state_t state;
} feedback_processor_t;

extern const uint16_t feedback_map_adc[FB_MAP_SIZE];
extern const uint8_t feedback_map_pos[FB_MAP_SIZE];

void feedback_processor_init(feedback_processor_t *inst);
bool feedback_processor_update(feedback_processor_t *inst, uint16_t adc_val);
bool feedback_processor_get(const feedback_processor_t *inst, uint8_t *pos);

#endif /* FEEDBACK_PROCESSOR_H */
