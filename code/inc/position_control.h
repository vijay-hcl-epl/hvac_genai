#ifndef POSITION_CONTROL_H
#define POSITION_CONTROL_H
#include <stdint.h>

void PC_Init(void);
void PC_NewCommand(int target_position);
void PC_LoopTask(void); // Called from main loop

#endif // POSITION_CONTROL_H
