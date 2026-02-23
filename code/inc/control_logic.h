#ifndef CONTROL_LOGIC_H
#define CONTROL_LOGIC_H
#include <stdint.h>
void ControlLogic_Init(void);
void ControlLogic_OnCommand(uint8_t position);
void ControlLogic_OnFeedbackUpdate(void);
#endif // CONTROL_LOGIC_H
