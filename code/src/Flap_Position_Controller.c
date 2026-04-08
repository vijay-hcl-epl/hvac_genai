#include "Flap_Position_Controller.h"

void Flap_Controller_Init(FlapPositionController_t *fc) {
    fc->state = FLAP_IDLE;
    fc->target_pos = 0;
    fc->current_pos = 0;
    fc->motor_on = 0;
    fc->error_flag = 0;
}

void Flap_Controller_Command(FlapPositionController_t *fc, int target) {
    fc->target_pos = target;
    fc->state = FLAP_MOVING;
    fc->motor_on = 1;
}

void Flap_Controller_Update(FlapPositionController_t *fc, int current_pos, int adc_valid) {
    fc->current_pos = current_pos;
    if (!adc_valid) {
        fc->error_flag = 1;
        fc->state = FLAP_FAULT;
        fc->motor_on = 0;
    } else if (fc->current_pos == fc->target_pos) {
        fc->state = FLAP_AT_TARGET;
        fc->motor_on = 0;
    }
}
