#ifndef STATUS_IND_H
#define STATUS_IND_H
#include <stdint.h>

// LED index: 0..5=flap pos, 6=power LED
void set_led_state(uint8_t idx);

#endif // STATUS_IND_H
