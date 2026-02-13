#ifndef FLAP_POS_CTRL_H
#define FLAP_POS_CTRL_H
#include <stdint.h>
#include <stdbool.h>

void flap_pos_ctrl_init(void);
void flap_pos_ctrl_set_target(uint8_t target_pos);
bool flap_pos_ctrl_movement_complete(void);
uint8_t flap_pos_ctrl_get_status(void);

#endif // FLAP_POS_CTRL_H
