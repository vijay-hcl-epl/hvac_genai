#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>
#include <stdbool.h>

// Flap Control Logic APIs
void FlapCtrlLogic_Init(void);
void FlapCtrlLogic_NewCmd(uint8_t pos);
void FlapCtrlLogic_RunCycle(void);
bool FlapCtrlLogic_MoveActive(void);

#endif // FLAP_CONTROL_LOGIC_H
