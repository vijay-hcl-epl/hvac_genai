#include "feedback_processor.h"
#include "main.h" // ADC_HANDLE

static uint16_t latest_adc = 0;
static uint8_t mapped_position = 0;
static bool valid = false;

// Example table: map ADC steps to logical positions
static const struct {uint16_t adc_min; uint16_t adc_max; uint8_t position;} position_map[] = {
    {0, 1000, 0x10},
    {1001, 2000, 0x20},
    {2001, 3000, 0x30},
    {3001, 4095, 0x40}
};

void feedback_processor_init(void) {
    latest_adc = 0;
    mapped_position = 0;
    valid = false;
}

void feedback_processor_update(void) {
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
        latest_adc = HAL_ADC_GetValue(&hadc1);
        valid = false;
        for (uint8_t i = 0; i < sizeof(position_map)/sizeof(position_map[0]); ++i) {
            if (latest_adc >= position_map[i].adc_min && latest_adc <= position_map[i].adc_max) {
                mapped_position = position_map[i].position;
                valid = true;
                break;
            }
        }
    } else {
        valid = false;
    }
}

uint8_t feedback_processor_get_position(bool *out_valid) {
    if (out_valid) *out_valid = valid;
    return mapped_position;
}
