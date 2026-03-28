#include "Electrical_Interface_Driver.h"

static drive_state_t drive_state = DRIVE_IDLE;

void EID_Init(void) {
    drive_state = DRIVE_IDLE;
}

void EID_Task(void) {
    // Hardware actuation logic
}

void EID_Actuate(uint8_t cmd) {
    if(cmd == 0) {
        drive_state = DRIVE_IDLE;
        // turn off outputs
    } else {
        drive_state = DRIVE_ACTIVE;
        // actuate output
    }
}
