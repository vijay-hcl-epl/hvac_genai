/* FlapControlLogic.h - Logic for determining and executing flap position changes. */
#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdint.h>
#include <stdbool.h>

void FlapControlLogic_Init(void);
void FlapControlLogic_SetTarget(uint8_t targetPos);
bool FlapControlLogic_Task(void); // Returns true if movement was required/performed
uint8_t FlapControlLogic_GetStatus(void);

#endif /* FLAP_CONTROL_LOGIC_H */
