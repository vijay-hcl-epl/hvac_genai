#ifndef FLAP_CONTROL_H
#define FLAP_CONTROL_H
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    FLAP_IDLE=0,
    FLAP_MOVING,
    FLAP_TARGET_REACHED,
    FLAP_FAULT
} FlapControlState_t;

void flap_control_init(void);
void flap_control_set_target(uint8_t pos); // 0–5
FlapControlState_t flap_control_get_status(void);
void flap_control_clear_fault(void);
uint8_t flap_control_get_position(void); // logical position (0-5)

#endif // FLAP_CONTROL_H
