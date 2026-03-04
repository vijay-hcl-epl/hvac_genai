#ifndef POSITION_CTRL_LOGIC_H
#define POSITION_CTRL_LOGIC_H
#include <stdint.h>
#include <stdbool.h>
void position_ctrl_logic_init(void);
void position_ctrl_step(void);
bool get_moving_status(void);
#endif // POSITION_CTRL_LOGIC_H
