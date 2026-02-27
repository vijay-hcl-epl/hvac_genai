#ifndef CONTROL_LOGIC_H
#define CONTROL_LOGIC_H

#include <stdint.h>
#include <stdbool.h>

void ControlLogic_Init(void);
void ControlLogic_Process(void);
bool ControlLogic_IsMoveComplete(void);

#endif // CONTROL_LOGIC_H
