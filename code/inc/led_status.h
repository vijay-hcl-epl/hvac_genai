#ifndef LED_STATUS_H
#define LED_STATUS_H
#include <stdint.h>
void led_status_init(void);
void led_status_update_position(uint8_t pos); // 0–5
void led_status_power_on(void);
#endif // LED_STATUS_H
