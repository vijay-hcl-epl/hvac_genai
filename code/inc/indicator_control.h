#ifndef INDICATOR_CONTROL_H
#define INDICATOR_CONTROL_H
#include <stdint.h>

void indicator_control_init(void);
void indicator_control_update(uint8_t logical_position, int sys_state);

#endif // INDICATOR_CONTROL_H
