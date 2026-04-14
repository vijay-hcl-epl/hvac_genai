#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdint.h>

void led_status_handler_init(void);
void led_position_set(uint8_t position); // One-hot position LED
void led_indicate_error(void);
void led_power_on(void);

#endif // LED_STATUS_HANDLER_H
