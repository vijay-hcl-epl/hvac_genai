#include "status_indication.h"
#include "hw_abstraction.h"
#include "config.h"

void StatusIndication_Init(void) {
    HWAbstraction_SetPowerLED(true);
    StatusIndication_Update(true, 0);
}

void StatusIndication_Update(bool power_on, uint8_t pos_idx) {
    HWAbstraction_SetPowerLED(power_on);
    for (uint8_t i = 0; i < Config_GetNumPositions(); ++i) {
        HWAbstraction_SetPositionLED(i, i == pos_idx);
    }
}

void StatusIndication_UpdateOnState(system_state_t state) {
    if (state == STATE_IDLE || state == STATE_STEADY) {
        StatusIndication_Update(true, PositionSensing_GetPosition());
    } else if (state == STATE_MOVING) {
        StatusIndication_Update(true, PositionSensing_GetPosition());
    } else if (state == STATE_ERROR) {
        StatusIndication_Update(false, 0);
    }
}
