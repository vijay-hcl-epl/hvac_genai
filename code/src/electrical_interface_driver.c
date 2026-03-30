#include "electrical_interface_driver.h"

static DriverState_t eid_state = DRIVER_IDLE;
static int32_t current_target = -1;

void EID_PerformOperation(int32_t target_position) {
    eid_state = DRIVER_ACTION;
    current_target = target_position;
    // Set hardware signals (stub)
    HAL_SetMotorPosition(target_position);
    eid_state = DRIVER_COMPLETE;
}

void EID_StopMotor(void) {
    // Stop motor output
    HAL_SetMotorPosition(-1);
}
