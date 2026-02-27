#ifndef POSITION_SENSING_H
#define POSITION_SENSING_H

#include <stdint.h>
#include <stdbool.h>

void PositionSensing_Init(void);
void PositionSensing_Update(void);
uint8_t PositionSensing_GetPosition(void);
bool PositionSensing_IsValid(void);

#endif // POSITION_SENSING_H
