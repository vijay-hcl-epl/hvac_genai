#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>

#define FLAP_POSITION_MIN            (0U)
#define FLAP_POSITION_MAX            (3U)

typedef enum
{
    FLAP_CONTROL_IDLE = 0,
    FLAP_CONTROL_MOVING,
    FLAP_CONTROL_TARGET_REACHED,
    FLAP_CONTROL_FAULT
} Flap_Control_State_t;

void Flap_Control_Logic_Init(void);
void Flap_Control_Logic_Process_Command(uint8_t target_position);
void Flap_Control_Logic_MainFunction(void);
Flap_Control_State_t Flap_Control_Logic_Get_State(void);

#endif
