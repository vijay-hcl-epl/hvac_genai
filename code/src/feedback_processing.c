#include "feedback_processing.h"
#include "hardware_abstraction.h"

// Example mapping table (calibration: should be maintained by config)
typedef struct {
    uint16_t adc_min;
    uint16_t adc_max;
    uint8_t position;
} position_map_t;

static const position_map_t pos_table[6] = {
    {0,  6554, 0},
    {6555, 13108, 1},
    {13109, 19662, 2},
    {19663, 26216, 3},
    {26217, 32770, 4},
    {32771, 40959, 5}
};

uint8_t Get_Current_Position(void) {
    uint16_t adc = ADC_Read(0);
    for (int i = 0; i < 6; i++) {
        if (adc >= pos_table[i].adc_min && adc <= pos_table[i].adc_max)
            return pos_table[i].position;
    }
    return 0xFF; // Invalid position
}
