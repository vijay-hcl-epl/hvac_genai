#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdbool.h>

void led_driver_init(void);
void led_driver_update(int position);
void led_driver_set_status_led(bool state);
void led_driver_signal_error(void);

#endif // LED_DRIVER_H
