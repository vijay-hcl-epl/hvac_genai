#ifndef FLAP_POSITION_CONTROLLER_H
#define FLAP_POSITION_CONTROLLER_H

#include <stdint.h>

void flap_position_controller_init(void);
void set_flap_target(uint16_t position);
void notify_position_update(uint16_t actual_position);

#endif // FLAP_POSITION_CONTROLLER_H
