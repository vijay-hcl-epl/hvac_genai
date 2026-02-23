#ifndef POSITION_SENSING_H
#define POSITION_SENSING_H

#include <stdint.h>
#include <stdbool.h>

// Logical position definitions
#define POSITION_INVALID 0xFF
#define FLAP_POSITION_MIN 0
#define FLAP_POSITION_MAX 5

void position_sensing_init(void);
uint8_t position_sensing_get_current_position(void);
bool position_sensing_is_valid_position(uint8_t logical_pos);
void position_sensing_periodic(void);

#endif // POSITION_SENSING_H
