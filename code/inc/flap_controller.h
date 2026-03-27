#ifndef FLAP_CONTROLLER_H
#define FLAP_CONTROLLER_H

#include <stdint.h>

// SWE-REQ-001, SWE-REQ-002
void FlapController_ReceiveAndValidateCommand(uint8_t requested_position);

// SWE-REQ-003
uint8_t FlapController_ReadCurrentPosition(void);

// SWE-REQ-004, SWE-REQ-005, SWE-REQ-006
void FlapController_UpdateMotor(uint8_t requested_position);

// SWE-REQ-007
void FlapController_UpdateStatusIndicator(void);

// Data structures for internal state
typedef enum {
    FLAP_IDLE = 0,
    FLAP_MOVING,
    FLAP_TARGET_REACHED,
    FLAP_INVALID_COMMAND
} FlapControlState_t;

typedef struct {
    uint8_t requested_position;
    uint8_t current_position;
    FlapControlState_t state;
} FlapController_t;

#endif // FLAP_CONTROLLER_H
