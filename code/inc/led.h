#ifndef LED_H
#define LED_H

#include <stdbool.h>
#include <stdint.h>

void led_init(void);
void led_update_state(bool system_on, int logical_pos, bool test_mode);

#endif // LED_H
