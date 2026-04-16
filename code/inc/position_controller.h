#ifndef POSITION_CONTROLLER_H
#define POSITION_CONTROLLER_H
#include <stdint.h>
#include <stdbool.h>

void PositionController_Init(void);
bool PositionController_RequestMove(uint8_t target_position);
void PositionController_MainLoop(void);

#endif // POSITION_CONTROLLER_H
