#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H

#include <stdbool.h>
#include <stdint.h>

void Flap_Control_Logic_Init(void);
void Flap_Control_Logic_IssueMovementCmd(uint8_t target_position);
void Flap_Control_Logic_MainTask(void);
bool Flap_Control_Logic_IsInMotion(void);
uint8_t Flap_Control_Logic_GetTargetPosition(void);

#endif /* FLAP_CONTROL_LOGIC_H */
