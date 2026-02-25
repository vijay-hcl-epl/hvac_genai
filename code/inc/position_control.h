#ifndef POSITION_CONTROL_H
#define POSITION_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

void PositionControl_Init(void);
void PositionControl_SetTarget(uint8_t position);
void PositionControl_UpdateCurrent(uint8_t position, bool valid_feedback);
void PositionControl_Process(void);

#endif // POSITION_CONTROL_H
