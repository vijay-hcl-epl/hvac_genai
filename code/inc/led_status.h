#ifndef LED_STATUS_H
#define LED_STATUS_H
#include <stdint.h>
void led_status_init(void);
// Sets all LEDs for power-on
void led_status_power_on(void);
// Updates position LEDs (only one enabled at a time)
void led_status_update_position(uint8_t pos);
// Shows error LED pattern
void led_status_error(void);
#endif
