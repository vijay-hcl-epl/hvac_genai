#ifndef FLAP_CONTROLLER_H
#define FLAP_CONTROLLER_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    FLAP_CTRL_IDLE = 0,
    FLAP_CTRL_MOVING,
    FLAP_CTRL_TARGET_REACHED
} FlapControllerState_t;

typedef enum {
    CTRL_ORDER_STOP = 0,
    CTRL_ORDER_MOVE_CW,
    CTRL_ORDER_MOVE_CCW
} ControlOrder_t;

void FlapController_Init(void);
void FlapController_Tick(void);

#endif // FLAP_CONTROLLER_H
