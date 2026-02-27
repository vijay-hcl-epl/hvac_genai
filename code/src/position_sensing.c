#include "position_sensing.h"
#include "config.h"
#include "hw_abstraction.h"

static uint8_t current_position = 0;
static bool valid_position = false;

void PositionSensing_Init(void) {
    current_position = 0;
    valid_position = false;
}

void PositionSensing_Update(void) {
    uint16_t adc_val = HWAbstraction_ReadADC();
    valid_position = Config_MapADCToPosition(adc_val, &current_position);
}

uint8_t PositionSensing_GetPosition(void) {
    return current_position;
}

bool PositionSensing_IsValid(void) {
    return valid_position;
}
