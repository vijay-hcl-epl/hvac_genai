#include "flap_position_ctrl.h"
// [TBD — Not in source]: ADC threshold table, Flash config
static FlapState g_flap_state = FLAP_IDLE;
void FlapCtrl_eval(uint8_t target_pos, uint16_t adc_val) {
    // [TBD — Implement threshold comparison logic, HW ADC table]
    if (adc_val != target_pos) g_flap_state = FLAP_MOVING;
    else g_flap_state = FLAP_TARGET;
}
FlapState FlapCtrl_status(void) { return g_flap_state; }
