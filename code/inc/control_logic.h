#ifndef CONTROL_LOGIC_H
#define CONTROL_LOGIC_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    CTRL_IDLE = 0,
    CTRL_MOVING,
    CTRL_ERROR
} CtrlState_t;

typedef enum {
    CTRL_OK = 0,
    CTRL_MOVEMENT_DONE,
    CTRL_ERROR_STATE
} CtrlStatus_t;

void ControlLogic_Init(uint8_t initial_position);
void ControlLogic_Task(void);
CtrlStatus_t ControlLogic_SetTargetPosition(int8_t pos);
uint8_t ControlLogic_GetCurrentPosition(void);
bool ControlLogic_MovementInProgress(void);
CtrlState_t ControlLogic_GetState(void);

#endif // CONTROL_LOGIC_H
