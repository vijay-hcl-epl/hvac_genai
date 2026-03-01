#ifndef FLAP_CONTROL_LOGIC_H
#define FLAP_CONTROL_LOGIC_H
#include <stdint.h>
#include <stdbool.h>
void flap_control_init(void);
void flap_control_event(void);
bool flap_control_is_busy(void);
uint8_t flap_control_get_target(void);
#endif // FLAP_CONTROL_LOGIC_H
