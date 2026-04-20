#ifndef LED_INDICATION_H
#define LED_INDICATION_H
#include <stdint.h>
#include <stdbool.h>
void update_position_led(uint8_t pos);
void set_error_led(void);
void set_status_led(bool on);
#endif // LED_INDICATION_H
