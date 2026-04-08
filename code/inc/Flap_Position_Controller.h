#ifndef FLAP_POSITION_CONTROLLER_H
#define FLAP_POSITION_CONTROLLER_H

typedef enum {
    FLAP_IDLE,
    FLAP_MOVING,
    FLAP_AT_TARGET,
    FLAP_FAULT
} FlapState_t;

typedef struct {
    FlapState_t state;
    int target_pos;
    int current_pos;
    int motor_on;
    int error_flag;
} FlapPositionController_t;

void Flap_Controller_Init(FlapPositionController_t *fc);
void Flap_Controller_Command(FlapPositionController_t *fc, int target);
void Flap_Controller_Update(FlapPositionController_t *fc, int current_pos, int adc_valid);

#endif // FLAP_POSITION_CONTROLLER_H
