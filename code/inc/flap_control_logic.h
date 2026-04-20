#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdbool.h>

void FlapControlLogic_Init(void);
void FlapControlLogic_ExecCycle(void);
bool FlapControlLogic_IsBusy(void);
bool FlapControlLogic_HasError(void);
void FlapControlLogic_Reset(void);

#endif // FLAP_CONTROL_LOGIC_H
