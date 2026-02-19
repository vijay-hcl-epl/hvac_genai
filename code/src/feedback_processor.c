#include "feedback_processor.h"
#include <stddef.h>

/* Example: 8-point mapping, adjust as needed */
const uint16_t feedback_map_adc[FB_MAP_SIZE] = {0, 500, 1000, 1500, 2000, 2500, 3000, 3500};
const uint8_t feedback_map_pos[FB_MAP_SIZE] = {0x00, 0x20, 0x40, 0x60, 0x80, 0xA0, 0xC0, 0xE0};

void feedback_processor_init(feedback_processor_t *inst)
{
    if (inst == NULL) { return; }
    inst->adc_sample = 0U;
    inst->position = 0U;
    inst->valid = false;
    inst->state = FB_STATE_INIT;
}

bool feedback_processor_update(feedback_processor_t *inst, uint16_t adc_val)
{
    if (inst == NULL) { return false; }
    bool found = false;
    for (unsigned int i = 0U; i < FB_MAP_SIZE; ++i) {
        if (adc_val < feedback_map_adc[i]) {
            inst->position = feedback_map_pos[i];
            found = true;
            break;
        }
    }
    if (!found) {
        inst->position = feedback_map_pos[FB_MAP_SIZE - 1];
    }
    inst->adc_sample = adc_val;
    inst->valid = (adc_val < 4096);
    inst->state = inst->valid ? FB_STATE_READY : FB_STATE_INVALID;
    return inst->valid;
}

bool feedback_processor_get(const feedback_processor_t *inst, uint8_t *pos)
{
    if (inst == NULL || pos == NULL) { return false; }
    if (inst->valid) {
        *pos = inst->position;
        return true;
    }
    return false;
}
