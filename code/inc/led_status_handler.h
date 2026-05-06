#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

void led_status_handler_init(void);
void led_set_power_led(bool on);
void led_set_position(uint8_t position);
void led_indicate_error(void);

#endif // LED_STATUS_HANDLER_H
