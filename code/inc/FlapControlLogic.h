#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    FLAP_IDLE = 0,
    FLAP_MOVING,
    FLAP_TARGET_REACHED,
    FLAP_FAULT
} FlapControlLogic_State_t;

void FlapControlLogic_Init(void);
void FlapControlLogic_Task(void);

#endif /* FLAP_CONTROL_LOGIC_H */
